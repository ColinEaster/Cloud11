#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "../game/gameobjectcontainer.h"
#include <vector>

/**
 * @brief compare Extra method used for shuffling the deck which compares one Card's sortValue to another
 *        in order to randomly distribute the cards across the deck. Used as a parameter for thisDeck.sort()
 * @param i First Card to compare.
 * @param j Second Card to compare.
 */
bool compare(Card i, Card j);

class Deck : public GameObjectContainer
{
private:
    /**
     * @brief thisDeck A vector of the cards in the deck. The first Card in thisDeck represents
     * the Card on the top of the deck, or the card to draw first.
     */
    std::vector<Card> thisDeck;
    /**
     * @brief iter The iterator to correspond to thisDeck.
     */
    std::vector<Card>::iterator iter;
public:

    /**
     * @brief deal Deal takes the top card of thisDeck and removes and returns it, similar to
     * a 'pop()' method.
     */
    Card deal();
    /**
     * @brief dealHand dealHand returns a vector of Cards of size i from the top of the deck in
     * the same order as they were in the deck.
     * @param i The amount of cards you wish to deal from the deck.
     */
    std::vector<Card> dealHand(int i);
    /**
     * @brief shuffle Generates sort values for all cards in the deck and uses a stl sort algorithm
     * to randomize the cards in the deck.
     */
    void shuffle();

    /**
     * @brief Deck Default constructor for Deck. This method constructs the deck with a default 52 cards, unshuffled
     * and all in order.
     */
    Deck();

    int size();

    void print();

    ~Deck();
};

#endif // DECK_H
