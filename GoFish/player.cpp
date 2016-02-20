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
#include "player.h"
#include <iostream>

Player::Player(std::vector<Card> Hand, std::string name, int clientID)
{
    this->name = name;
    thisHand = Hand;
    this->clientID  = clientID;
    score = 0;
}

Player::Player(std::string name, int clientID)
{
    this->name = name;
    thisHand = std::vector<Card>();
    this->clientID  = clientID;
    score = 0;
}

Player::Player(std::vector<Card> Hand, std::string name)
{
    this->name = name;
    thisHand = Hand;
    score = 0;
}

Player::Player(std::vector<Card> Hand)
{
    thisHand = Hand;
    score = 0;
}

Player::Player(std::string name)
{
    thisHand = std::vector<Card>();
    this->name = name;
    score = 0;
}

Player::Player()
{
    this->name = "NULL";
    score = 0;
}

void Player::setName(std::string name)
{
    this->name = name;
}

void Player::addCards(std::vector<Card> Cards)
{
    for(iter = Cards.begin(); iter != Cards.end(); iter++)
    {
        thisHand.push_back(*iter);
    }
}

void Player::addCard(Card newCard)
{
    thisHand.push_back(newCard);
}

std::string Player::getName()
{
    return name;
}

std::vector<Card> Player::putDown(int rank)
{
    std::vector<Card> Down = std::vector<Card>();

    int check = 0;

    for(iter = thisHand.begin(); iter != thisHand.end(); iter++)
    {
        if(iter->getRank() == rank)
        {
            check++;
        }
    }
    if(check >= 4)
    {
        for(iter = thisHand.begin(); iter != thisHand.end(); iter++)
        {
            if(iter->getRank() == rank)
            {
                Down.push_back(*iter);
                thisHand.erase(iter);
                iter = thisHand.begin();
            }
        }
    }
    return Down;
}

std::vector<Card> Player::query(int rank)
{
    std::vector<Card> Hand = std::vector<Card>();
    for(iter = thisHand.begin(); iter != thisHand.end(); iter++)
    {
        if(iter->getRank() == rank)
        {
            Hand.push_back(*iter);
            thisHand.erase(iter);
            iter = thisHand.begin();
        }
    }
    return Hand;
}

bool Player::checkWin()
{
    return thisHand.size() == 0;
}

int Player::getScore()
{
    return score;
}

int Player::getClientID()
{
    return clientID;
}

void Player::incrementScore()
{
    //Increments Score by one
    score ++;
}

void Player::printHand()
{
    for(iter = thisHand.begin(); iter != thisHand.end(); iter++)
    {
        iter->print();
        std::cout << std::endl;
    }
}

int Player::amountOf(int rank)
{
    int i = 0;
    for(iter = thisHand.begin(); iter != thisHand.end(); iter++)
    {
        if(iter->getRank() == rank)
        {
            i++;
        }
    }
    return i;
}

void Player::setScore(int score)
{
    this->score = score;
}

void Player::setHand(std::vector<Card> Hand)
{
    thisHand = Hand;
}

std::vector<Card> Player::getHand()
{
    return thisHand;
}

Player::~Player()
{
}
