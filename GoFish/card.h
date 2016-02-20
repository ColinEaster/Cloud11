#ifndef CARD_H
#define CARD_H
#include "../game/gameobject.h"
#include <string>

class Card : public GameObject
{
private:
    /**
     * @brief suit The suit of a card describes both its color and attribute.
     * A suit of 1 represents Hearts
     * A suit of 2 represents Diamonds
     * A suit of 3 represents Clubs
     * A suit of 4 represents Spades
     *
     * A suit of 0 is reserved for Jokers
     */
    int suit;

    /**
     * @brief rank The rank of a card describes its power and number.
     * A rank of 1 represents an Ace
     * A rank of 2-10 represent number cards 2-10 respectively
     * A rank of 11 represents a Jack
     * A rank of 12 represents a Queen
     * A rank of 13 represents a King
     *
     * A rank of 0 is reserved for Jokers
     */
    /**
     * @brief sortValue The sort value is a special value used by a Deck to shuffle cards.
     * This value should ideally be randomly generated, and should never be used outside
     * of sorting algorithms.
     */
public:
    /**
     * @brief Card Default Constructor for a Card, constructs a Joker, as no proper parameters
     * have been provided. This method initializes sortValue to 0.
     */
    Card();
    /**
     * @brief Card Secondary Constructor for a Card, takes two arguments 'suit' and 'rank'.
     * This method initializes sortValue to 0.
     * @param suit The suit of the given card you wish to make
     * @param rank The rank off the given card you wish to make
     */
    Card(int suit,int rank);

    /**
     * @brief print Prints to cout the name of the card in <rank> of <suit>s format.
     * If the card is a Joker then only Joker is printed.
     * 'Impossible Card' will be printed if one or more of the parameters are out of their respective
     * ranges.
     */
    void print();

    /**
     * @brief getRankName Analogous to print method, but only returns the name for a given rank
     * and returns it as a string, instead of printing it to cout.
     */
    static std::string getRankName(int rank);

    /**
     * @brief generateSortValue This method generates a random value between 0 and deckSize and assigns it
     * to sortValue. Generating this value will appropriately assign values for the cards to be sorted.
     * @param deckSize The size of the deck the card is a part of, so that the card has a correct chance
     * of being above or below another card in the same deck.
     */
    void generateSortValue(int rand, int DeckSize);

    /**
     * @brief getSortValue Returns the current sortValue, used for the compare() method in the shuffle algorithm.
     */
    int getSortValue();

    /**
     * @brief getRank Returns the rank of the card.
     */
    int getRank();

    /**
     * @brief getSuit Returns the suit of the card.
     */
    int getSuit();

    /**
     * @brief toFilename Returns a string of the card in a former which lends itself to calling the correct card from
     * a library of images.
     */
    std::string toFilename();

    /**
     * @brief getType This method runs through if statements to determine what kind of rank the string in question is referring to
     * @param s A generic name for a rank of Cards
     * @return An integer value which corresponds to the rank the given string represented.
     */
    static int getType(std::string s);
};

#endif // CARD_H
