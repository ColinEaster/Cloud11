#include "testcard.h"
#include "../GoFish/card.h"
TestCard::TestCard()
{
}

TEST(Card, rank)
{
    Card c = Card(3,4);
    ASSERT_EQ(4, c.getRank());
}

TEST(generateSortValue, withinDeckSize)
{
    Card c = Card(3,4);
    c.generateSortValue(12,52);
    ASSERT_TRUE(c.getSortValue() <= 52);
}

TEST(getRankName, zero)
{
    Card c = Card();
    std::string s = c.getRankName(0);
    ASSERT_EQ("Joker", s);
}

TEST(getRankName, greaterThan13)
{
    Card c = Card();
    std::string s = c.getRankName(15);
    ASSERT_EQ("15", s);
}

TEST(getRankName, Queen)
{
    Card c = Card();
    std::string s = c.getRankName(12);
    ASSERT_EQ("Queen", s);
}

TEST(getType, incorrectAnswer)
{
    Card c = Card();
    ASSERT_EQ(0,c.getType("vhusdddddfj"));
}

TEST(getType, pluralanswer)
{
    Card c = Card();
    ASSERT_EQ(2,c.getType("twos"));
}

TEST(getType, numberAnswer)
{
    Card c = Card();
    ASSERT_EQ(2,c.getType("2"));
}

TEST(ToFileName, ImpossibleCard)
{
    Card c = Card(5,14);
    ASSERT_EQ("red_joker", c.toFilename());
}

TEST(ToFileName, FaceCard)
{
    Card c = Card(4,13);
    ASSERT_EQ("king_of_spades2", c.toFilename());
}

TEST(ToFileName, NumberCard)
{
    Card c = Card(4,6);
    ASSERT_EQ("6_of_spades", c.toFilename());
}
