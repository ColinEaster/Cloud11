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
#include "gofishclient.h"
#include "../GoFishServer/gfservermess.h"
#include <iostream>
#include <string>

GoFishClient::GoFishClient(Player p, Socket* socket) : Game(socket)
{
    Me = p;
    Them = std::vector<Player>();
    turnCounter = 0;
    winCheck = false;
}

void GoFishClient::run()
{
    while(!winCheck)
    {
        if(turnCounter == 0)
        {
            turn();
            turnCounter ++;
            ReceiveEndTurn *m = new ReceiveEndTurn();
            socket->send(m);
            delete m;
        }
    }
}

void GoFishClient::turn()
{
    bool askedYet = false;

    //GUI replacement needed

    std::cout << Me.getName()  << ", what would you like to do?:" << std::endl;
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
            //GUI removes the need for this option
        }
        else if(menuValue == 1 && askedYet)
        {
            std::cout << "You already asked!\n";
        }
        else if(menuValue == 1)
        {
            ask();
            askedYet = true;
        }
        else if(menuValue == 0)
        {
            putDown();
        }
    }
}

void GoFishClient::ask()
{
    std::cout << "What rank of card would you like to ask " + Them.begin()->getName() + " for?\n";

    std::string s;

    getline(std::cin, s);

    int rank = Card::getType(s);

    Ask *m = new Ask(rank);
    socket->send(m);
    delete m;

    //Expect ReceiveCards or ReceiveGoFishClient
}

void GoFishClient::putDown()
{
    std::cout << "What rank of card would you like to put down?\n";

    std::string s;

    getline(std::cin, s);

    int rank = Card::getType(s);

    if(Me.amountOf(rank)>=4)
    {
        PutDown *m = new PutDown(rank);
        socket->send(m);
        delete m;
    }
    else
    {
        std::cout << "You don't have enough of that card to do that.\n";
    }

    //Expect to Receive Update to Score
}

int GoFishClient::menu()
{
    //Presumably GUI stuff will replace this.

    std::cout << "0 - Put Down\n1 - Ask\n2 - See Cards\n3 - End Turn\n";

    int decis;

    std::cin >> decis;

    //get rid of extra input after cin
    std::string dummy;

    std::getline(std::cin, dummy);

    return decis;
}

void GoFishClient::handle(AllPlayers* message)
{
    std::vector<Player>::iterator i = std::vector<Player>::iterator();

    for(i = message->thesePlayers.begin(); i != message->thesePlayers.end(); i++)
        if(i->getClientID() != Me.getClientID())
            Them.push_back(*i);
    turnCounter = message->thesePlayers.size();
}

void GoFishClient::handle(StartingPlayer* message)
{
    if(Me.getClientID() == message->clientID)
    {
        turnCounter = 0;
    }
    else
    {
        int i = 0;
        for(std::vector<Player>::iterator iter = Them.begin(); iter != Them.end(); iter++)
        {
            i++;
            if(iter->getClientID() == message->clientID)
            {
                turnCounter = i;
                return;
            }
        }
        turnCounter = Them.size()+1;
        std::cerr << "ERROR: Starting Player doesn't match any IDs";
    }
}

void GoFishClient::handle(ReceiveHand* message)
{
    Me.addCards(message->Hand);
}

void GoFishClient::handle(ReceiveCards* message)
{
    std::cout << Them.begin()->getName() << " gave " << Me.getName();
    //Print amount of cards
    std::cout << message->Cards.size();
    std::cout << " ";
    //Print Rank Name
    std::cout << Card::getRankName(message->Cards.begin()->getRank()) << "s\n";
    Me.addCards(message->Cards);
}

void GoFishClient::handle(TurnEnd* message)
{
    //This increments turnCounter by one
    turnCounter ++;

    if(turnCounter == Them.size()+1)
    {
        turnCounter = 0;
    }
}

//When someone asks you
void GoFishClient::handle(AskEventPersonal* message)
{
    std::cout << Them.end()->getName() << " asked you for " << message->askRank << "\n";

    Me.query(message->askRank);

    if(Me.amountOf(message->askRank)!=0)
    {
        std::cout << "You gave them " << Me.amountOf(message->askRank) << " " << Card::getRankName(message->askRank) << "\n";
    }
    else
    {
        std::cout << "Go Fish!";
    }
}

//When someone else asks someone else
void GoFishClient::handle(AskEvent* message)
{
    std::cout << (Them.begin()+turnCounter-1)->getName() << " asked " << (Them.begin()+turnCounter)->getName() << " for " << message->askRank << "\n";
}

void GoFishClient::handle(AskEvent_Size* message)
{
    std::cout << (Them.begin()+turnCounter)->getName() << " gave them " << message->Size << "\n";
}

void GoFishClient::handle(AskEvent_Fish* message)
{
    std::cout << (Them.begin()+turnCounter+1)->getName() << " went fishing!\n";
}

void GoFishClient::handle(ReceiveWinString* message)
{
    winCheck = false;
    std::cout << message->winString << "\n";
}

void GoFishClient::handle(UpdateScore* message)
{
    Me.setScore(message->Score);
}

void GoFishClient::handle(ReceiveFish* message)
{
    std::cout << "Go Fish!\n You received a ";
    message->Fish.print();
    Me.addCard(message->Fish);
}

