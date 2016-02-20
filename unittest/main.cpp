#include <iostream>
#include <string>
#include "gtest/gtest.h"

#include "../game/gameobjectcontainer.h"
#include "../game/gameobject.h"
#include "../game/abstractplayer.h"

#include "../GoFish/deck.h"
#include "../GoFish/card.h"
#include "../GoFish/player.h"

#include "testcard.h"
#include "testplayer.h"
#include "testtable.h"
#include "testdeck.h"

using namespace std;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestAbstractPlayer, ForAddObjects)
{
    AbstractPlayer * player =  new AbstractPlayer("Player");
    EXPECT_EQ("Player", player->getName());
    GameObject * g =new GameObject();
    player->addObject(*g);
    EXPECT_EQ(1, player->getObjects().size());
    std::vector<GameObject> v = std::vector<GameObject>();
    v.push_back(GameObject());
    v.push_back(GameObject());
    player->addObjects(new GameObjectContainer(v));
    EXPECT_EQ(3, player->getObjects().size());
    delete player;
    delete g;
}

//TEST(TestGameObjectContainer, ForDeal){
//    GameObjectContainer * container = new GameObjectContainer();
//    container->addToEnd(GameObject(1));
//    container->addToEnd(GameObject(2));

//    ASSERT_EQ(2,container->size());

//    GameObjectContainer * dealtContainer;
//    dealtContainer = container->deal(1);
//    ASSERT_EQ(1,dealtContainer->size());
//    ASSERT_EQ(1,dealtContainer->size());
//    ASSERT_EQ(1,dealtContainer->popBack()->getRank());

//    ASSERT_EQ(1,container->size());
//    container->deal(1);
//    ASSERT_EQ(1,container->size());
//}
