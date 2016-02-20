#ifndef GOFISHSERVER_H
#define GOFISHSERVER_H
#include "../GoFish/player.h"
#include "../GoFish/deck.h"
#include "../GoFish/table.h"
#include "gfservermess.h"
#include "../server/messagehandler.h"
#include "../GameServer/gameserver.h"

class GoFishServer : public GameServer
{
private:
    /**
     * @brief Pool The Deck used for this game. This Deck starts with 52 cards at the beginning of the game
     * but may be subject to removal. At the end of the game, the deck should have no cards left in it.
     */
    Deck Pool;
    /**
     * @brief Players A list of Players in the game.
     *
     * 0 - First     ^
     * 1 - Second    |   Right
     * 2 - Third     |
     * ...           |   Left
     * n - Last      v
     */
    std::vector<Player> Players;
    /**
     * @brief iter An iterator corresponding the Players in the game.
     */
    std::vector<Player>::iterator iter;
    /**
     * @brief thisTable The table corresponding to this game. The table holds pairs of cards that players have put
     * down.
     */
    Table thisTable;

    /**
     * @brief tieCheck Boolean which is ticked true if the game has tied between two or more players. This boolean only turns on or off
     * in the findWinner() method. It is checked in the win() method when announcing the winner of the game.
     */
    bool tieCheck;
    /**
     * @brief tiedPlayers A list of tied players to print in the win() method. This vector is reinitialized at the beginning of
     * every run of findWinner() and is only really used for name values.
     */
    std::vector<Player> tiedPlayers;
public:
    GoFishServer(int port);

    void startGame();

    void handle(int clientID, PutDown *message);
    void handle(int clientID, Ask *message);
    void handle(int clientID, ReceiveEndTurn *message);
};

#endif // GOFISH_H
