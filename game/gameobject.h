#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
protected:
    int rank;
    int sortValue;

public:
    GameObject();
    GameObject(int arank);
    /**
     * @brief Gets the number of the card (the rank).
     * @return the rank of the card (i.e. 2, 3, 13 (king) as an integer
     */
    int getRank();
    /**
     * @brief Gets the sorting value of the object.
     * @return the sort value as an integer
     */
    int getSortValue();
    /**
     * @brief Prints information about the object.
     */
    virtual void print();
    /**
     * @brief Generates a sort value for the object.
     */
    void generateSortValue();

    virtual ~GameObject();
};

#endif // GAMEOBJECT_H
