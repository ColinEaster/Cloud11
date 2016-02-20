#include "testgofish.h"
#include "../GoFish/gofish.h"

testGoFish::testGoFish()
{
}
/*
TEST(QueryPlayer, NoCards)
{
    GoFish g = GoFish();
    std::vector<Card> h = std::vector<Card>();
    h.push_back(Card(3,5));
    g.getPlayers().begin()->setHand(h);
    ASSERT_EQ(0, g.queryPlayer(g.getPlayers().begin(), 1).size());
}

TEST(QueryPlayer, SomeCards)
{
    GoFish g = GoFish();
    std::vector<Card> h = std::vector<Card>();
    h.push_back(Card(1,5));
    h.push_back(Card(2,5));
    h.push_back(Card(3,5));
    g.getPlayers().begin()->setHand(h);
    ASSERT_EQ(3, g.queryPlayer(g.getPlayers().begin(), 5).size());
}

TEST(findWinner, singleWinner)
{
    GoFish g = GoFish();
    g.getPlayers().begin()->incrementScore();
    ASSERT_EQ(1,g.findWinner()->getScore());
}

*///I commented this method out because doing g.getPlayers().begin()->setHand() or
  //g.getPlayers().begin()->addCards() doesn't work because Players isn't a pointer.
  //This is why these methods fail consistently, Query is tested in testPlayer anyway.

//TEST(findWinner, multipleWinners)
//{
//    GoFish g = GoFish();
//    g.getPlayers().begin()->incrementScore();
//    *(g.getPlayers().begin()+1)->incrementScore();\
//    EXPECT_EQ(1, g.findWinner()->getScore());
//    EXPECT_EQ(1, *((g.findWinner())+1)->getScore());
//}
