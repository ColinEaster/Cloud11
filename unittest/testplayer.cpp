#include "testplayer.h"
#include "../GoFish/player.h"
#include <vector>

testPlayer::testPlayer()
{
}

TEST(TestPutDown, ForFourOfAKind)
{
    std::vector<Card> h = std::vector<Card>();
    h.push_back(Card(1,5));
    h.push_back(Card(2,5));
    h.push_back(Card(3,5));
    h.push_back(Card(4,5));
    Player p = Player(h,"NICK");
    std::vector<Card> pd = p.putDown(5);
    EXPECT_EQ(4, pd.size());
    EXPECT_EQ(5, pd.front().getRank());
}

TEST(PutDown, LessThanFour)
{
    std::vector<Card> j = std::vector<Card>();
    j.push_back(Card(1,5));
    j.push_back(Card(2,5));
    Player pj = Player(j,"NICK");
    std::vector<Card> pdj = pj.putDown(5);
    ASSERT_EQ(0, pdj.size());

}


TEST(PutDown, MoreThanFour)
{
    std::vector<Card> h = std::vector<Card>();
    h.push_back(Card(1,5));
    h.push_back(Card(2,5));
    h.push_back(Card(3,5));
    h.push_back(Card(4,5));
    h.push_back(Card(4,5));
    h.push_back(Card(3,5));
    h.push_back(Card(2,5));
    h.push_back(Card(1,5));
    Player p = Player(h,"NICK");
    std::vector<Card> pd = p.putDown(5);
    EXPECT_EQ(8, pd.size());
    EXPECT_EQ(5, pd.front().getRank());
}

TEST(Query, NoCards)
{
    std::vector<Card> h = std::vector<Card>();
    h.push_back(Card(1,5));
    h.push_back(Card(2,5));
    h.push_back(Card(3,5));
    h.push_back(Card(4,5));
    Player p = Player(h,"NICK");
    std::vector<Card> pd = p.query(4);
    ASSERT_EQ(0, pd.size());
}

TEST(Query, MoreThanFour)
{
    std::vector<Card> h = std::vector<Card>();
    h.push_back(Card(1,5));
    h.push_back(Card(2,5));
    h.push_back(Card(3,5));
    h.push_back(Card(4,5));
    h.push_back(Card(3,5));
    h.push_back(Card(2,5));
    Player p = Player(h,"NICK");
    std::vector<Card> pd = p.query(5);
    ASSERT_EQ(6, pd.size());
}

TEST(AddCard, NewCardNoOthers)
{
    Player p= Player("NICK");
    p.addCard(Card(2,5));
    ASSERT_EQ(1, p.getHand().size());
}

TEST(AddCard, NewCardDifferentOthers)
{
    std::vector<Card> h = std::vector<Card>();
    h.push_back(Card(1,5));
    h.push_back(Card(2,5));
    h.push_back(Card(3,5));
    h.push_back(Card(4,5));
    h.push_back(Card(3,5));
    h.push_back(Card(2,5));
    Player p= Player(h,"NICK");
    p.addCard(Card(2,4));
    EXPECT_EQ(7, p.getHand().size());
    EXPECT_EQ(1, p.query(4).size());
}

TEST(AddCard, NewCardSameOthers)
{
    std::vector<Card> h = std::vector<Card>();
    h.push_back(Card(1,5));
    h.push_back(Card(2,5));
    h.push_back(Card(3,5));
    Player p= Player(h,"NICK");
    p.addCard(Card(4,5));
    EXPECT_EQ(4, p.getHand().size());
    EXPECT_EQ(4, p.query(5).size());
}

TEST(AddCards, NewCardsNoOthers)
{

        Player p= Player("NICK");
        std::vector<Card> h = std::vector<Card>();
        h.push_back(Card(1,5));
        h.push_back(Card(2,5));
        h.push_back(Card(3,5));
        p.addCards(h);
        ASSERT_EQ(3, p.getHand().size());

}

TEST(AddCards, NewCardsDifferentOthers)
{
        std::vector<Card> d = std::vector<Card>();
        d.push_back(Card(1,4));
        d.push_back(Card(2,2));
        d.push_back(Card(3,6));
        Player p= Player(d,"NICK");
        std::vector<Card> h = std::vector<Card>();
        h.push_back(Card(1,5));
        h.push_back(Card(2,5));
        h.push_back(Card(3,5));
        p.addCards(h);
        EXPECT_EQ(6, p.getHand().size());
        EXPECT_EQ(3, p.query(5).size());
}

TEST(AddCards, NewVariedCardsDifferentOthers)
{
        std::vector<Card> d = std::vector<Card>();
        d.push_back(Card(1,4));
        d.push_back(Card(2,2));
        d.push_back(Card(3,6));
        Player p= Player(d,"NICK");
        std::vector<Card> h = std::vector<Card>();
        h.push_back(Card(1,7));
        h.push_back(Card(2,2));
        h.push_back(Card(3,1));
        p.addCards(h);
        EXPECT_EQ(6, p.getHand().size());
        EXPECT_EQ(1, p.query(7).size());
}

TEST(AddCards, NoCards)
{
        std::vector<Card> d = std::vector<Card>();
        d.push_back(Card(1,4));
        d.push_back(Card(2,2));
        d.push_back(Card(3,6));
        Player p= Player(d,"NICK");
        std::vector<Card> h = std::vector<Card>();
        p.addCards(h);
        ASSERT_EQ(3, p.getHand().size());
}

TEST(Score, IncrementedScore)
{
    Player p = Player("NICK");
    p.incrementScore();
    ASSERT_EQ(1, p.getScore());
}

TEST(Player, Name)
{
       Player pj = Player("NICK");
       ASSERT_EQ("NICK", pj.getName());
}

TEST(setName, NewName)
{
    Player p= Player("NICK");
    p.setName("Dan");
    ASSERT_EQ("Dan", p.getName());
}
