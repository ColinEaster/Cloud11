#include "client_controller.h"
#include "../client_GUI/client_gui.h"
#include <map>
#include <string>
#include <QDebug>

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
    if(gameName == "Nim"){
        makeGameServer(port_num);
    }
}

void ClientController::makeGameServer(int port){
    qDebug() << "make game server";
    server = new GameServer(port);

    // connect the client to the newly created server
    clientSocket = new Socket(ipToConnectTo.c_str(), port, this);
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
    gameGui = new Nim_GUI();
    // create Nim game and connect slots



    gameGui->show();
    clientGui->hide();
}

void ClientController::mapClientAndServerFunctions(){
    //serverCreationFunctions.insert(std::make_pair("Nim", &ClientController::makeGameServer) );
    //serverCreationFunctions["Nim"] = &ClientController::makeGameServer;
    clientGuiCreationFunctions.insert({"Nim", "makeNimGameAndGui"});
    qDebug() << "result of map: " << clientGuiCreationFunctions["Nim"];
}

/**
 * @brief ClientController::handle
 * Update the player list in Joined lobby/host lobby
 */
void ClientController::handle(UpdateLobby *msg)
{
    emit updatePlayerList(msg->playerlist);

}
/**
 * @brief client_GUI::handle Handles a successful join lobby message from the server.
 * @param message contains the type of game that will be played.
 */
void ClientController::handle(JoinLobbySuccess *message)
{

    gameChosen = message->gameType;

}


/**
 * @brief client_GUI::handle
 * Update the chat messages
 */
void ClientController::handle(ChatIncoming *msg)
{
    chatwindow-> addChatString(msg->chatString);
}

/**
 * @brief client_GUI::handle
 * Update the chat messages
 */
void ClientController::handle(NimIncoming *msg)
{
    std::cout << "incoming nim message";
}

void ClientController::handle(GameStart *) {
    // qt gui functions have to be called in the main thread
    QMetaObject::invokeMethod(this, "startGameReceived", Qt::QueuedConnection);
}
//std::map<std::string, ClientController::serverFunction> ClientController::serverFunctions = { { "Nim", &(client_GUI::makeServer<GameServer>) }, { "Go Fish", &(client_GUI::makeServer<GameServer>) } };
