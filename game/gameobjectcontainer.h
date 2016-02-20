#ifndef GAMEOBJECTCONTAINER_H
#define GAMEOBJECTCONTAINER_H
#include <vector>
#include "gameobject.h"

class GameObjectContainer
{
protected:
    std::vector<GameObject> objects;
    std::vector<GameObject>::iterator iter;


public:
    GameObjectContainer();
    /**
     * @brief GameObjectContainer creates a GameObjectContainer and adds objects from vector to class vector
     * @param objs objects to add
     */
    GameObjectContainer(std::vector<GameObject> objs);
    /**
     * @brief Returns and removes the last object in the container (the back end).
     * @return The last object in the container.
     */
    GameObject * popBack();

    /**
     * @brief Returns and removes the first object in the container.
     * @return The first object in the container.
     */
    GameObject popFront();
    /**
     * @brief Shuffles the objects according to their sort values.
     */
    void shuffle();

    /**
     * @brief Deals the given number of GameObjects from the container.
     * @param The number of objects you want to deal.
     * @return The GameObjects that were dealt inside a container.
     */
    virtual GameObjectContainer * deal(int i);
    /**
     * @brief Adds the given GameObject to the end of the container.
     * @param The object you want to add.
     */
    void addToEnd(GameObject a);
    /**
     * @brief The number of objects in the container (the size).
     * @return The number of objects in the container.
     */
    virtual int size();
    /**
     * @brief addObjects adds objects from one GameObjectContainer to the other
     * @param g GameObkectContainer whose items are added to this conatiner
     */
    void addObjects(GameObjectContainer g);
    /**
     * @brief getContainer returns the vector of GameObjects
     * @return vector of gameobjects
     */
    std::vector<GameObject> getContainer();
    virtual ~GameObjectContainer();
};

#endif // GAMEOBJECTCONTAINER_H
