#ifndef GOFISH_H
#define GOFISH_H
#include "player.h"
#include "deck.h"
#include "table.h"

class GoFish
{
private:
    /**
     * @brief Pool The Deck used for this game. This Deck starts with 52 cards at the beginning of the game
     * but may be subject to removal. At the end of the game, the deck should have no cards left in it.
     */
    Deck Pool;
    /**
     * @brief Players A list of Players in the game.
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
    /**
     * @brief queryPlayer queryPlayer is a method which returns the query of the given Player. This method is more or less
     * a wrapper for the query method which finds, removes, and returns all cards of 'rank' in a Player's hand.
     * @param iter The Player who has been asked for cards of a certain kind.
     * @param rank The certain kind of cards the given Player has been asked for.
     * @return A vector of Cards containing all of the cards of rank 'rank' that the given Player has been queried for.
     */
    std::vector<Card> queryPlayer(std::vector<Player>::iterator iter, int rank);
    /**
     * @brief run This method controls the game's functioning. It iterates through each player and calls turn() for them.
     * if a Player's win conditions have been met, the loop breaks and calls the win() method for that player.
     */
    void run();
    /**
     * @brief turn Takes a Player and gives them the option to put down a four of a kind or ask someone for cards. It does this
     * by calling the menu() function for an appropriate menu value and calls ask() or putDown() in place of that value.
     * @param iter The given Player whose turn it is.
     */
    void turn(std::vector<Player>::iterator iter);
    /**
     * @brief win Displays win information for the Player who's win conditions hold true.
     * @param iter The Player who won.
     */
    void win(std::vector<Player>::iterator iter);
    /**
     * @brief ask Prompts the current user for a rank to ask the Player on their left for and queries said Player. If the Query returns
     * an empty vector, the Player then is told "Go Fish!" and picks up a card from the deck. If not, the Player receives the vector
     * of cards and adds it to their hand.
     * @param iter The Player whose turn it is.
     */
    void ask(std::vector<Player>::iterator iter);
    /**
     * @brief putDown Prompts the Player for a rank of cards to put down on the table. If the Player does not have four cards of the
     * same kind in the rank they specified, then they are told that they have not met the requirements to put down and their turn ends.
     * @param iter The Player whose turn it is.
     */
    void putDown(std::vector<Player>::iterator iter);

    /**
     * @brief menu Provides the Player with options for their turn. If the Player inputs a 2, they end their turn. If the Player
     * inputs a 1, they opt to put down their cards, calling putDown(). If the Player inputs a 0, they opt to ask the Player to their left for a
     * certain rank of cards, calling ask().
     * @return Returns an int value which corresponds to these actions, which are ultimately called in turn()
     */
    int menu();

    /**
     * @brief findWinner Iterates through and finds the Player(s) with the highest score. Players with the same score are stored
     * in tiedPlayers and the tieCheck is ticked on to signify that more than one Player has won the game.
     * @return
     */
    std::vector<Player>::iterator findWinner();

    std::vector<Player> getPlayers();
    bool getTieCheck();

    /**
     * @brief GoFish Constructing a GoFish object initializes Players, Pool, and Table and shuffles Pool.
     */
    GoFish();
    ~GoFish();
};

#endif // GOFISH_H
