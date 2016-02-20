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
protected:
    bool gameNotOver;
    bool startingPlayer;
    bool checkForGameOver();
    void waitForOpponent();
    vector<std::string> * log;
    Nim_GUI * gui;


public:
    bool opponentMoveReceived;
    Nim();
    Nim(Socket * client_socket);
    /**
     * @brief Method that is called at the start of the game.
     */
    void run();
    void gameOver();
    void wait(int seconds);
    void makeMove();

    void handle(PlayerRemovedItems *message);
    void handle(PlayerTurn * message);



};

#endif // NIM_H
