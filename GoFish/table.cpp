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
#include "table.h"

Table::Table()
{
    FourOfAKinds = std::vector<std::vector<Card> >();
}

void Table::add(std::vector<Card> newCards)
{
    FourOfAKinds.push_back(newCards);
}

std::vector<Card> Table::get(int rank)
{
    std::vector<Card>::iterator insideIter;
    for(iter = FourOfAKinds.begin(); iter != FourOfAKinds.end(); iter++)
    {
        if(iter->begin()->getRank() == rank)
        {
            return *iter;
        }
    }
    return std::vector<Card>();
}

Table::~Table()
{

}

