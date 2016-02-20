#include "testdeck.h"

testDeck::testDeck()
{
}

//Put the method you're testing first, then the specific case you're testing with
TEST(dealHand, dealMoreCardsThanDeckHas)
{
    Deck d = Deck();

    std::vector<Card> v = d.dealHand(53);

    //When you have more than one assert statement you need to use EXPECT instead of ASSERT
    //otherwise only the first value acts as a test.
    EXPECT_EQ(v.size(),52);
    EXPECT_EQ(d.size(),0);
}
//Try making algorithms which can test every possible scenario for errors
TEST(dealHand, dealAllSizeCases)
{
    Deck d;

    for(int i = 0; i <= 52; i ++)
    {
        d = Deck();
        EXPECT_EQ(d.dealHand(i).size(),i);
    }
}

//Test cases which should never happen, and fix them in the main code in case they
//make an error. But most of all, prioritize full testing of the program!
TEST(dealHand, negativeValue)
{
    Deck d = Deck();

    ASSERT_EQ(d.dealHand(-1).size(),0);
}

//Making small cases like this ensures that you know where the error is. And most of
//all, it's quick, and it looks impressive.
TEST(deal, sizeChanges)
{
    Deck d = Deck();

    d.deal();

    ASSERT_EQ(d.size(), 51);
}


//Good Luck! Testing is quick and pretty simple if done right. If something's wrong in the code, try to fix it!
