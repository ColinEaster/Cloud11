#ifndef AbstractPlayer_H
#define AbstractPlayer_H
#include "gameobjectcontainer.h"
#include <string>
#include "../server/clientid.h"

class AbstractPlayer
{
protected:
    GameObjectContainer hand;
    std::string name;
    ClientID id;

public:
    AbstractPlayer();
    AbstractPlayer(GameObjectContainer objs);
    AbstractPlayer(std::string aname);
    /**
     * @brief Gets the name of the AbstractPlayer.
     * @return A string representing the name of the AbstractPlayer.
     */
    std::string getName();
    /**
     * @brief Sets the name of the AbstractPlayer to the given string.
     * @param The new name of the AbstractPlayer.
     */
    void setName(std::string s);
    /**
     * @brief Returns the container of GameObjects that the AbstractPlayer owns.
     * @return A GameObjectContainer that the AbstractPlayer owns.
     */
    GameObjectContainer getObjects();
    /**
     * @brief getID Gets the id of the client.
     * @return the id of the client (an int).
     */
    ClientID getID();

    virtual bool checkWin();
    /**
     * @brief Adds an object to the AbstractPlayer's container.
     * @param GameObject to be added to the AbstractPlayer's container.
     */
    void addObject(GameObject obj);
    /**
     * @brief Adds the GameObjects in the GameObjectContainer to the AbstractPlayer's inventory
     * @param GameObjectContainer to add to the AbstractPlayer.
     */
    void addObjects(GameObjectContainer * objs);

    virtual ~AbstractPlayer();
};

#endif // AbstractPlayer_H
