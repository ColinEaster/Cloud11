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
#include "deck.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

Deck::Deck()
{
    thisDeck = std::vector<Card>();
    for(int i = 1; i < 5; i++)
    {
        for(int j = 1; j < 14; j++)
        {
            thisDeck.push_back(Card(i,j));
        }
    }
}

Card Deck::deal()
{
    iter = thisDeck.begin();
    Card temp = *iter;
    thisDeck.erase(thisDeck.begin());
    return temp;
}

std::vector<Card> Deck::dealHand(int i)
{
    int limit = thisDeck.size();
    std::vector<Card> Hand = std::vector<Card>();
    for(int j = 0; j < i && j < limit; j++)
    {
        Hand.push_back(deal());
    }
    return Hand;
}

void Deck::shuffle()
{
    srandom(time(NULL));

    for(iter = thisDeck.begin(); iter != thisDeck.end(); iter ++)
        iter->generateSortValue(rand(), thisDeck.size());
    std::sort(thisDeck.begin(),thisDeck.end(), compare);
}

void Deck::print()
{
    for(iter = thisDeck.begin(); iter != thisDeck.end(); iter++)
    {
        iter->print();
        std::cout << std::endl;
    }
}

int Deck::size()
{
    return thisDeck.size();
}

Deck::~Deck()
{
}

bool compare(Card i, Card j)
{
    return i.getSortValue() < j.getSortValue();
}
