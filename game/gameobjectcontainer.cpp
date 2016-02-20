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
#include "gameobjectcontainer.h"
#include "gameobject.h"
#include <algorithm>

bool compare(GameObject i, GameObject j)
{
    return i.getSortValue() < j.getSortValue();
}

GameObjectContainer::GameObjectContainer()
{
    objects = std::vector<GameObject>();
}

GameObjectContainer::GameObjectContainer(std::vector<GameObject> objs)
{
    objects = objs;
}

GameObject * GameObjectContainer::popBack()
{

    GameObject * object;
    object = &objects.back();
    objects.pop_back();
    return object;

}
GameObject GameObjectContainer::popFront()
{
    iter = objects.begin();
    GameObject temp = *iter;
    objects.erase(objects.begin());
    return temp;
}

void GameObjectContainer::shuffle()
{
    for(iter = objects.begin(); iter != objects.end(); iter ++)
        iter->generateSortValue();
    std::sort(objects.begin(),objects.end(), compare);
}

void GameObjectContainer::addToEnd(GameObject a)
{
    objects.push_back(a);
}
GameObjectContainer * GameObjectContainer::deal(int i)
{
    GameObjectContainer * container = new GameObjectContainer();
    int number = 0;

    for(int n = 0; n < i; n++){

    if(objects.size() == 0)
        break;

    container->addToEnd(objects.back());
    objects.pop_back();
    number++;
    }

    if(number == 0)
        return NULL;

    return container;
}

int GameObjectContainer::size()
{
    return objects.size();
}

void GameObjectContainer::addObjects(GameObjectContainer g)
{
    std::vector<GameObject> objs = g.getContainer();
    std::vector<GameObject>::iterator i;
    for(i = objs.begin(); i != objs.end(); i++)
    {
        this->addToEnd(*i);
    }
}

std::vector<GameObject> GameObjectContainer::getContainer()
{
    return objects;
}

GameObjectContainer::~GameObjectContainer()
{
}




