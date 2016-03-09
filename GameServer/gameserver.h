#ifndef GAMESERVER_H
#define GAMESERVER_H
#include "gamestart.h"
#include "gameover.h"
#include "../server/servermessagehandler.h"
#include "../server/clientid.h"
#include "../server/message.h"
#include "../server/messagetype.h"
#include "../server/serversocket.h"
#include "../server/messages.h"
#include <vector>
#include <map>

class client_GUI;

class GameServer:public ServerMessageHandler
{
    friend class client_GUI;
protected:

    /**
     * @brief player A vector of client ID's
     */
    std::vector<ClientID> player;

    /**
     * @brief userNameMap A map connecting client ID numbers to player names.
     */
    std::map<ClientID,std::string> userNameMap;

public:
    GameServer();
    /**
     * @brief GameServer A server that accepts clients in a lobby and can play a game.
     * @param port The port used for communication.
     */
    GameServer(int port);
    /**
     * @brief socket Socket used to send messages.
     */
    ServerSocket * socket;
    /**
     * @brief gameOver Called when the game ends.
     * @return
     */
    virtual bool gameOver();
    /**
     * @brief startGame Can be called to do things before the game starts.
     */
    virtual void startGame();

    /**
     * @brief Handles how the server reacts to a game over message from the host.
     * @param message received from the host to end the game
     */
    void handle(ClientID client, GameOver *message);
    /**
     * @brief Handles how the server reacts to a message to start the game
     * @param message received from host client to start the game
     */
    void handle(ClientID client, GameStart *message);
    /**
     * @brief Handles how the server reacts to a message from the client saying the game over message was received and the game was ended
     * @param message received from client by server indicating success in ending the game
     */
    void handle(ClientID client, GameOverSuccess *message);
    /**
     * @brief Handles how the server reacts to the client saying they failed to end the game
     * @param message received from client by server indicating failure to end the game
     */
    void handle(ClientID client, GameOverFailure *message);
    /**
     * @brief Handles how the server reacts to a successful game start message.
     * @param message received from a client that started the game
     */
    void handle(ClientID client, GameStartSuccess *message);
    /**
     * @brief Handles how the server reacts to a failure to start the game message.
     * @param message received from a client that couldn't start the game
     */
    void handle(ClientID client, GameStartFailure *message);
    /**
     * @brief handle Handles how the server reacts to a join lobby message from a client.
     * @param client The client the message came from.
     * @param message The message received from a client indicating intent to join the lobby.
     */
    void handle(ClientID client, JoinLobby *message);
    /**
     * @brief handle Handles how the server responds to a chat message from a client (it broadcasts it to all clients).
     * @param client The client from whom the message was received.
     * @param message The chat message.
     */
    void handle(ClientID client, ChatInput *message);
    /**
     * @brief handle Handles how the server reacts to an input from a client playing Nim (they took away some stones).
     * @param client The client the message is from.
     * @param message The message containing the number of stones removed.
     */
    void handle(ClientID client, NimInput *message);


    ~GameServer();


};

#endif // GAMESERVER_H
