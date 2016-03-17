#ifndef NIM_H
#define NIM_H

#include <QWidget>
#include "../client_GUI/nim_gui.h"
#include "../game/game.h"
#include "nim_messages.h"
#include "../server/messagehandler.h"
#include "../server/clientsocket.h"
#include "../server/messages.h"
#include "../server/formatutils.h"
#include <vector>
#include <string.h>
#include <mutex>
#include "../NimServer/nimserver.h"
#include "../server/clientsocket.h"

class Nim:public Game
{

    Q_OBJECT

public:
    bool yourTurn;


    Nim(){};
    Nim(Socket * client_socket);
    Nim(Socket *client_socket, std::vector<std::string> playerList, std::string playerName, bool hosting);
    void gameOver();



    void handle(PlayerRemovedItems *message);
    void handle(PlayerTurn * message);
    void handle(NimIncoming *msg);

public slots:
    void receiveUserWantsToRemoveStones(int);
    void startGame();
    void nimIncomingMessageReceived(int);

    void mainThreadEndGame();

signals:
    void removeStones(int);
    void displayStones(int);
    void displayMessage(std::string);
    void sendPlayerList(std::vector<std::string>);
    void allowInput(std::string, bool);

private:
    const std::string Error_Message = "You can't choose that amount!";
    int numStones = 20;
    bool gameNotOver;
    bool startingPlayer;
    std::vector<std::string> log;
    std::string playerName;
    std::string opponentName;
    std::vector<int> amountsThatCanBeRemoved;

    void endTheGame();
    bool checkForGameOver();
    bool checkIfNumberOfStonesIsValid(const int &num);



};

#endif // NIM_H
