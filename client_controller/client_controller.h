#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <string>
#include <map>
#include "../client_GUI/client_gui.h"

class ClientController: public QObject, public MessageHandler
{
    Q_OBJECT

public:
    ClientController();
    ~ClientController();

    // message handlers
    void handle(UpdateLobby *msg);
    void handle(JoinLobbySuccess *message);
    void handle(ChatIncoming *msg);
    void handle(GameStart *);



public slots:
    void receiveUserName(std::string name);
    void receiveIP(std::string ip);
    void receiveHostDecision(bool wantsToHost);
    void receiveGameNameDecision(std::string);
    void startGamePressed(); // only the host can press this
    void startGameReceived(); // called on receipt of start game message

    void makeNimGameAndGui();
    void emitUpdatePlayerList(UpdateLobby* msg);
    void gameQuit();
    void receivedPassedChatMessage(ChatIncoming* message);

signals:
    void updatePlayerList(std::vector<string>);

protected:
    client_GUI* clientGui;
    chat* chatwindow;

    GameServer* server;

    Socket* clientSocket;

    QWidget* gameGui;
    Game* game;

private:
    static const int port_num = 31460;

    void startGame(std::string gameName){};
    void mapClientAndServerFunctions();

    void createAppropriateGameServer(std::string gameName);
    void connectToClientGui();
    void createSocketAndConnectToServer();

    // server creation functions
    void makeGameServer();

    // client creation functions

    void createChat();

    //typedef GameServer* (ClientController::*serverFunction)(int);
    //typedef Game* (*clientFunction)(Socket*);
    //typedef std::map<std::string, serverFunction> serverCreationFunctionMap;
    //serverCreationFunctionMap serverCreationFunctions;
    std::map<std::string, const char*> clientGuiCreationFunctions;

    std::string gameChosen = "";
    std::string playerName = "";
    std::string ipToConnectTo = "127.0.0.1";
    std::vector<std::string> playerList;

    bool isHosting = false;


};

//Q_DECLARE_METATYPE(std::vector<string>)

#endif // CLIENTCONTROLLER_H
