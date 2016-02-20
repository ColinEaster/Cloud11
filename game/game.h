#ifndef GAME_H
#define GAME_H
#include "gameobject.h"
#include <vector>
#include "abstractplayer.h"
#include "../GameServer/gameover.h"
#include "../GameServer/gamestart.h"
#include "../server/messagehandler.h"
#include "../server/clientsocket.h"

class Game:public MessageHandler
{
protected:
    /**
     * @brief objects A container of game objects
     */
    GameObjectContainer * objects;
    /**
     * @brief players A vector of players
     */
    std::vector<AbstractPlayer> * players;
    /**
     * @brief iter An iterator for the vector of players
     */
    std::vector<AbstractPlayer>::iterator iter;
    /**
     * @brief socket A socket used to send messages to the server
     */
    Socket * socket;

public:
    Game();
    /**
     * @brief Game Creates a client version of a game
     * @param client_socket A socket for which this class will be the handler of (i.e. this class can take over the socket from client_gui)
     */
    Game(Socket * client_socket);
    /**
     * @brief The method that runs when the game starts.
     */
    virtual void run() = 0;

    /**
     * @brief Method called when the game over message is received from the server.
     */
    virtual void gameOver() = 0;

    /**
     * @brief Handles receiving a game over message from the server
     * @param message received from the server indicating the game is over
     */
    void handle(GameOver *message);
    /**
     * @brief Handles receiving a game start message from the server by calling the run method.
     * @param message from server indicating the game is starting
     */
    void handle(GameStart *message);

    ~Game();
};
#endif // GAME_H
