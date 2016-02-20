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
#include "gofish.h"
#include <iostream>
#include <string>

GoFish::GoFish()
{
    Pool = Deck();

    Pool.shuffle();

    Players = std::vector<Player>();

    Players.push_back(Player(Pool.dealHand(7), "Dan"));
    Players.push_back(Player(Pool.dealHand(7), "Nick"));
    Players.push_back(Player(Pool.dealHand(7), "Colin"));
    Players.push_back(Player(Pool.dealHand(7), "Aaron"));

    thisTable = Table();
}

void GoFish::run()
{
    bool winCheck = true;
    while(winCheck)
    {
        for(iter = Players.begin(); iter != Players.end(); iter++)
        {
            std::cout << iter->getName() << "'s turn has begun!\n";
            turn(iter);
            if(iter->checkWin() || Pool.size() == 0)
            {
                winCheck = false;
                break;
            }
        }
    }
    iter = findWinner();
    win(iter);
}

void GoFish::win(std::vector<Player>::iterator iter)
{
    if(tieCheck)
    {
        std::cout << "Congratulations, ";

        std::cout << tiedPlayers.begin()->getName() << " ";

        for(std::vector<Player>::iterator i = tiedPlayers.begin() + 1; i != tiedPlayers.end(); i++)
        {
            std::cout << "and " << i->getName() << " ";
        }

        std::cout << std::endl;
    }
    else
    {
        std::cout << "Congratulations, " << iter->getName();
    }
}

std::vector<Player>::iterator GoFish::findWinner()
{
    tieCheck = false;
    int max = Players.begin()->getScore();
    std::vector<Player>::iterator returnIterator = Players.begin();
    tiedPlayers = std::vector<Player>();
    for(iter = Players.begin() + 1; iter != Players.end(); iter++)
    {
        if(iter->getScore() > max)
        {
            tieCheck = false;
            tiedPlayers = std::vector<Player>();
            max = iter->getScore();
            returnIterator = iter;
        }
        else if(iter->getScore() == max)
        {
            tieCheck = true;
            tiedPlayers.push_back(*returnIterator);
            tiedPlayers.push_back(*iter);
        }
    }
    return returnIterator;
}

void GoFish::turn(std::vector<Player>::iterator iter)
{
    bool askedYet = false;
    std::cout << iter->getName()  << " what would you like to do?:" << std::endl;
    while(1)
    {
        int menuValue = menu();
        if(menuValue == 3 && !askedYet)
        {
            std::cout << "You still need to ask another Player!\n";
        }
        else if(menuValue == 3)
        {
            break;
        }
        else if(menuValue == 2)
        {
            iter->printHand();
        }
        else if(menuValue == 1 && askedYet)
        {
            std::cout << "You already asked!\n";
        }
        else if(menuValue == 1)
        {
            ask(iter);
            askedYet = true;
        }
        else if(menuValue == 0)
        {
            putDown(iter);
        }
    }
}

void GoFish::ask(std::vector<Player>::iterator iter)
{
    std::cout << "What rank of card would you like to ask Player " + (iter+1)->getName() + " for?\n";

    std::string s;

    getline(std::cin, s);

    int rank = Card::getType(s);

    std::vector<Card> Cards = queryPlayer(iter+1, rank);

    //DEBUG CODE
    for(std::vector<Card>::iterator i = Cards.begin(); i != Cards.end(); i++)
    {
        std::cout << "DEBUG: " << iter->getName() << " : ";
        i->print();
        std::cout << "\n";
    }

    if(Cards.size() == 0)
    {
        std::cout << "Go Fish!\n";
        Card temp = Pool.deal();
        std::cout << "You got a ";
        temp.print();
        std::cout << "\n";
        iter->addCard(temp);
    }
    else
    {
        std::cout << "Player " + (iter+1)->getName() + " has ";
        std::cout << Cards.size() << std::endl;
    }

    (iter)->addCards(Cards);
}

std::vector<Card> GoFish::queryPlayer(std::vector<Player>::iterator iter, int rank)
{
    return iter->query(rank);
}

void GoFish::putDown(std::vector<Player>::iterator iter)
{
    std::cout << "What rank of card would you like to put down?\n";

    std::string s;

    getline(std::cin, s);

    int rank = Card::getType(s);

    std::vector<Card> Cards = iter->putDown(rank);

    if(Cards.size() == 4)
    {
        thisTable.add(Cards);

    }
    else
    {
        std::cout << "Sorry, but you didn't have enough of that card to put down.\n";
    }
}

int GoFish::menu()
{
    std::cout << "0 - Put Down\n1 - Ask\n2 - See Cards\n3 - End Turn\n";

    int decis;

    std::cin >> decis;

    //get rid of extra input after cin
    std::string dummy;

    std::getline(std::cin, dummy);

    return decis;
}

std::vector<Player> GoFish::getPlayers()
{
    return Players;
}

bool GoFish::getTieCheck()
{
    return tieCheck;
}

GoFish::~GoFish()
{

}

