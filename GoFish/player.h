#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "../game/abstractplayer.h"
#include <vector>
#include <string>

class Player : public AbstractPlayer
{
private:
    /**
     * @brief thisHand thisHand represents the Player's hand, it's a vector of Cards which represents what Cards the Player
     * is currently in possession of. These cards should be only visible to this player.
     */
    std::vector<Card> thisHand;
    /**
     * @brief iter Iterator which corresponds to Card values.
     */
    std::vector<Card>::iterator iter;
    /**
     * @brief name The Player's name, used in the GoFish class to call a Player by name.
     */
    std::string name;
    /**
     * @brief score Keeps the Player's score. This variable should increment once every time they put down a four of a kind.
     */
    int score;

    int clientID;

public:
    /**
     * @brief putDown Takes an integer rank and compares it to every card in the hand, adding it to a vector of Cards. If the
     * vector is of size 4 (or greater), then the method deletes these cards from the Player's hand. Regardless of how many cards
     * are in the vector, it is returned at the end of the method.
     * @param rank The integer which corresponds to the rank of cards the Player is looking to put down. Each Player's goal is to place
     * sets of four down on the table, so rank indicates the common value between these cards, i.e. Jacks or Ones or Aces.
     */
    std::vector<Card> putDown(int rank);
    /**
     * @brief query This method is similar to putDown in that it finds and returns all cards of a given rank, but it deletes them from
     * the hand regardless of how many cards have been found in the hand.
     */
    std::vector<Card> query(int rank);
    /**
     * @brief checkWin Checks a win condition: The Player has no more cards in their hand.
     * @return true if thisHand.size() == 0
     */
    bool checkWin();

    std::string getName();
    void setName(std::string name);

    /**
     * @brief addCards Appends a given vector of Cards to the end of the Player's hand.
     */
    void addCards(std::vector<Card> Cards);
    /**
     * @brief addCard Appends a given Card to the end of the Player's hand.
     */
    void addCard(Card newCard);

    /**
     * @brief Player Constructs a Player with only a Hand based on a given Vector of Cards.
     */
    Player(std::vector<Card> Hand);
    /**
     * @brief Player Constructs a Player with only their name, useful for clientside views of multiplayer games, as the Player
     * should not know the internal information of other Player's save for their names.
     */
    Player();
    Player(std::string name);
    Player(std::string name, int clientID);
    Player(std::vector<Card> Hand, std::string name);
    Player(std::vector<Card> Hand, std::string name, int clientID);

    int amountOf(int rank);

    int getScore();
    void setScore(int score);

    void setHand(std::vector<Card> Hand);

    int getClientID();
    void incrementScore();
    void printHand();
    std::vector<Card> getHand();
    ~Player();
};

#endif // PLAYER_H
