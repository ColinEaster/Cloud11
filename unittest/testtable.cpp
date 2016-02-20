#include "testtable.h"
#include "../GoFish/card.h"

testTable::testTable()
{
}

TEST(TestAdd, MultipleFourOfAKinds)
{
    Table t = Table();

    std::vector<Card> c = std::vector<Card>();
    c.push_back(Card(2,1));
    c.push_back(Card(2,2));
    c.push_back(Card(2,3));
    c.push_back(Card(2,4));
    std::vector<Card> c2 = std::vector<Card>();
    c.push_back(Card(3,1));
    c.push_back(Card(3,2));
    c.push_back(Card(3,3));
    c.push_back(Card(3,4));
    std::vector<Card> c3 = std::vector<Card>();
    c.push_back(Card(4,1));
    c.push_back(Card(4,2));
    c.push_back(Card(4,3));
    c.push_back(Card(4,4));

    t.add(c);
    t.add(c2);
    t.add(c3);
    std::vector<Card> a = t.get(1);
    EXPECT_EQ(2, a.front().getSuit());
    EXPECT_EQ(4, t.get(3).size());
    std::vector<Card>::iterator i = t.get(4).begin()++;
    EXPECT_TRUE(t.get(4).front().getSuit() == i->getSuit());
}
