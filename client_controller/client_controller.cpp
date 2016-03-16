#include "client_controller.h"
#include "../client_GUI/client_gui.h"
#include <map>
#include <string>
#include <QDebug>
#include "../Nim/nim.h"

ClientController::ClientController()
{
    // fill the function map
    mapClientAndServerFunctions();

    // start the gui
    clientGui = new client_GUI();

    // connect to the gui slots and signals
    connectToClientGui();

    clientGui->show();

}

ClientController::~ClientController(){
    delete clientGui;
    delete chatwindow;
}

void ClientController::connectToClientGui(){
    qRegisterMetaType< std::vector<string> >("std::vector<string>");

    QObject::connect(this,&ClientController::updatePlayerList,clientGui, &client_GUI::receiveUpdatedPlayerList);
    QObject::connect(clientGui, &client_GUI::nameEntered, this, &ClientController::receiveUserName);
    QObject::connect(clientGui, &client_GUI::hostDecision, this, &ClientController::receiveHostDecision);
    QObject::connect(clientGui, &client_GUI::ipAddressEntered, this, &ClientController::receiveIP);
    QObject::connect(clientGui, &client_GUI::gameChosenInGui, this, &ClientController::receiveGameNameDecision);
    QObject::connect(clientGui, &client_GUI::startGamePressed, this, &ClientController::startGamePressed);
}

void ClientController::receiveUserName(std::__1::string name){
    playerName = name;
}

void ClientController::receiveGameNameDecision(string gameNameFromSignal){
    gameChosen = gameNameFromSignal;
    qDebug() << "received game name: " << gameChosen.c_str();
    createAppropriateGameServer(gameChosen);
}

void ClientController::receiveHostDecision(bool wantsToHost){
    isHosting = wantsToHost;
}

void ClientController::receiveIP(std::__1::string ip){
    ipToConnectTo = ip;

    if(!isHosting)
        createSocketAndConnectToServer();
}

void ClientController::startGamePressed(){
    qDebug() << "start game pressed";
    GameStart message(42);
    server->socket->broadcast(&message);
}

// called in main thread by handler of gameStart message
void ClientController::startGameReceived(){
    //const char* funcName = clientGuiCreationFunctions[gameChosen];
    //qDebug() << "game start handler called with function: " << funcName;
    qDebug() << "game received";
    if(gameChosen == "Nim"){
        makeNimGameAndGui();
    }
}

void ClientController::createAppropriateGameServer(string gameName){
    qDebug() << "make appropriate game server";
    if(gameName == "Nim")
        makeGameServer();

}

void ClientController::makeGameServer(){
    qDebug() << "make game server";
    server = new GameServer(port_num);

    createSocketAndConnectToServer();


}

void ClientController::createSocketAndConnectToServer(){
    // connect the client to the newly created server
    qDebug() << "creating client socket";
    clientSocket = new Socket(ipToConnectTo.c_str(), port_num, this);
    clientSocket->connect();

    // create a message to join the lobby
    JoinLobby *jl = new JoinLobby(playerName);
    clientSocket->send(jl);

    createChat();
}

void ClientController::createChat(){
    chatwindow = new chat();
    chatwindow->setClientSocket(clientSocket);
    chatwindow->show(); // Show the chat
}

void ClientController::makeNimGameAndGui(){
    qDebug() << "make nim game and gui";
    Nim_GUI* nimGui = new Nim_GUI();
    gameGui = nimGui;
    // create Nim game and connect slots
    qDebug() << "creating game";
    Nim* nimGame = new Nim(clientSocket, playerList, playerName, isHosting);
    game = nimGame;

    qDebug() << "connecting signals and slots";
    qRegisterMetaType<ChatIncoming*>("ChatIncoming*");
    QObject::connect(nimGui,&Nim_GUI::playerWantsToRemoveStones,nimGame, &Nim::receiveUserWantsToRemoveStones);
    QObject::connect(nimGame,&Nim::displayMessage,nimGui,&Nim_GUI::displayMessage);
    QObject::connect(nimGame, &Nim::displayStones, nimGui,&Nim_GUI::displayStones);
    QObject::connect(nimGame, &Nim::sendPlayerList, nimGui, &Nim_GUI::updatePlayerList);
    QObject::connect(nimGame, &Nim::allowInput, nimGui, &Nim_GUI::announce_current_player);
    QObject::connect(nimGame, &Nim::quitGame, this, &ClientController::gameQuit);
    QObject::connect(nimGame, &Nim::passChatMessage, this, &ClientController::receivedPassedChatMessage);

    gameGui->show();
    clientGui->hide();
    qDebug() << "starting game";
    nimGame->startGame();
}

void ClientController::gameQuit(){
    gameGui->hide();
    delete gameGui;
    delete game;
    clientGui->show();
}

void ClientController::mapClientAndServerFunctions(){
    //serverCreationFunctions.insert(std::make_pair("Nim", &ClientController::makeGameServer) );
    //serverCreationFunctions["Nim"] = &ClientController::makeGameServer;
    clientGuiCreationFunctions.insert({"Nim", "makeNimGameAndGui"});
    qDebug() << "result of map: " << clientGuiCreationFunctions["Nim"];
}
void ClientController::emitUpdatePlayerList(UpdateLobby* msg){
    playerList = msg->playerlist;
    emit updatePlayerList(msg->playerlist);
    delete msg;
}

/**
 * @brief ClientController::handle
 * Update the player list in Joined lobby/host lobby
 */
void ClientController::handle(UpdateLobby *msg)
{
    //QMetaObject::invokeMethod(this, "emitUpdatePlayerList", Qt::QueuedConnection, Q_ARG(UpdateLobby*, msg));
    this->playerList = msg->playerlist;
    emit updatePlayerList(msg->playerlist);
    delete msg;
}
/**
 * @brief client_GUI::handle Handles a successful join lobby message from the server.
 * @param message contains the type of game that will be played.
 */
void ClientController::handle(JoinLobbySuccess *message)
{

    gameChosen = message->gameType;

}

void ClientController::receivedPassedChatMessage(ChatIncoming *message){
    handle(message);
}

/**
 * @brief client_GUI::handle
 * Update the chat messages
 */
void ClientController::handle(ChatIncoming *msg)
{
    chatwindow-> addChatString(msg->chatString);
}


void ClientController::handle(GameStart *) {
    // qt gui functions have to be called in the main thread
    QMetaObject::invokeMethod(this, "startGameReceived", Qt::QueuedConnection);
}
//std::map<std::string, ClientController::serverFunction> ClientController::serverFunctions = { { "Nim", &(client_GUI::makeServer<GameServer>) }, { "Go Fish", &(client_GUI::makeServer<GameServer>) } };
