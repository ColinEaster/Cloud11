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
#include "card.h"
#include <iostream>
#include <string>


using namespace std;

Card::Card()
{
    suit = 0;
    rank = 0;
    sortValue = 0;
}

Card::Card(int suit, int rank)
{
    this->suit = suit;
    this->rank = rank;
    sortValue = 0;
}

void Card::generateSortValue(int rand, int DeckSize)
{
    sortValue = rand % DeckSize;
}

void Card::print()
{
    //Error Testing
    if(suit > 4 || suit < 0 || rank > 13 || rank < 0)
    {
        cout << "Impossible Card";
        return;
    }

    //Check for Joker
    if(suit == 0 || rank == 0)
    {
        cout << "Joker";
        return;
    }

    //Print <rank>
    if(rank == 1)
    {
        cout << "Ace of ";
    }
    else if(rank == 11)
    {
        cout << "Jack of ";
    }
    else if(rank == 12)
    {
        cout << "Queen of ";
    }
    else if(rank == 13)
    {
        cout << "King of ";
    }
    else
    {
        cout << rank << " of ";
    }

    //Print <suit>s
    if(suit == 1)
    {
        cout << "Hearts";
        return;
    }
    else if(suit == 2)
    {
        cout << "Diamonds";
        return;
    }
    else if(suit == 3)
    {
        cout << "Clubs";
        return;
    }
    else if(suit == 4)
    {
        cout << "Spades";
        return;
    }
}

std::string Card::getRankName(int rank)
{
    //Check for Joker
    if(rank == 0)
    {
        return "Joker";
    }

    if(rank == 1)
    {
        return "Ace";
    }
    else if(rank == 11)
    {
        return "Jack";
    }
    else if(rank == 12)
    {
        return "Queen";
    }
    else if(rank == 13)
    {
        return "King";
    }
    else
    {
        return "" + rank;
    }
}

int Card::getSortValue()
{
    return sortValue;
}

int Card::getRank()
{
    return rank;
}

int Card::getSuit()
{
    return suit;
}

int Card::getType(std::string s)
{

    if(s == "2" || s == "two" || s == "Two" || s == "TWO" || s == "twos")
    return 2;


    if(s =="3" || s == "three" || s == "THREE" || s == "threes")
    return 3;

    if(s == "4" || s == "four" || s == "FOUR" || s == "fours")
    return 4;

    if(s == "5" || s == "five" || s == "FIVE" || s == "fives")
    return 5;

    if(s == "6" || s == "six" || s == "SIX" || s == "sixes")
    return 6;

    if(s == "7" || s == "seven" || s== "SEVEN" || s == "sevens")
        return 7;

    if(s == "8" || s == "eight" || s == "EIGHT" || s == "eights")
        return 8;

    if(s == "9" || s == "nine" || s == "NINE" || s == "nines")
        return 9;

    if(s == "10" || s == "ten" || s == "TEN" || s == "tens")
        return 10;

    if(s == "JACK" || s == "jacks" || s == "jack")
        return 11;

    if(s == "QUEEN" || s == "queens" || s == "queen")
        return 12;

    if(s == "KING" || s == "king" || s == "kings")
        return 13;

    if(s == "ACE" || s == "ace" || s == "aces")
        return 1;

    return 0;
}

std::string Card::toFilename()
{
    std::string c = "";

    //Error Testing
    if(suit > 4 || suit < 0 || rank > 13 || rank < 0)
    {
        cout << "Impossible Card";
        return "red_joker";
    }

    //Joker Testing
    if(suit == 0 || rank == 0)
    {
        return "red_joker";
    }

    //<rank>
    if(rank == 1)
    {
        c = "ace_of_";
    }
    else if(rank == 11)
    {
        c = "jack_of_";
    }
    else if(rank == 12)
    {
        c = "queen_of_";
    }
    else if(rank == 13)
    {
        c = "king_of_";
    }
    else
    {
        c = rank;
        c = c + "_of_";
    }

    //<suit>
    if(suit == 1)
    {
        c = c + "hearts";
    }
    else if(suit == 2)
    {
        c = c + "diamonds";
    }
    else if(suit == 3)
    {
        c = c + "clubs";
    }
    else if(suit == 4)
    {
        c = c + "spades";
    }

    //To get the correct format of face cards.
    if(rank > 10 && rank < 14)
    {
        c = c + "2";
    }

    return c;
}
