/* Copyright 2015 Colin Easter, Daniel Turchiano, Wah Loon Keng, Aaron Willey, and Nicholas Turney.

    This file is part of Cloud11.

    Cloud11 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Cloud11 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Cloud11.  If not, see <http://www.gnu.org/licenses/>.

    */
#include "gameobject.h"
#include <stdlib.h>
#include <time.h>
/**
 * @brief GameObject::GameObject set sortValue to 0
 */
GameObject::GameObject()
{
   sortValue = 0;
}
/**
 * @brief GameObject::GameObject sets sortValue to zero and takes an int to set the rank to
 * @param arank rank to give the object
 */
GameObject::GameObject(int arank)
{
    rank = arank;
    sortValue = 0;
}

int GameObject::getRank()
{
    return rank;
}

int GameObject::getSortValue()
{
    return sortValue;
}

/**
 * @brief GameObject::generateSortValue generates a random value and sets the sortValue to it
 */
void GameObject::generateSortValue()
{
    srandom(time(NULL));
    sortValue = rand();
}
/**
 * @brief GameObject::print print values stored by object
 */
void GameObject::print()
{
}

GameObject::~GameObject()
{
}
