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
#include "gofishserver.h"
#include <iostream>
#include <string>

GoFishServer::GoFishServer(int port) : GameServer(port)
{
}

void GoFishServer::startGame()
{
    Pool = Deck();

    Pool.shuffle();

    Players = std::vector<Player>();

    for(std::map<ClientID,std::string>::iterator it = userNameMap.begin(); it != userNameMap.end(); ++it )
    {
        int tempID = it->first;
        std::string tempName = it->second;

        Players.push_back(Player(tempName,tempID));
    }

    //Send Players to each Client

    for(std::vector<Player>::iterator i = Players.begin(); i != Players.end(); i++)
    {
        std::vector<Card> temp = Pool.dealHand(7);
        i->addCards(temp);
        //Send cards to player of that ID
    }
}

void GoFishServer::handle(int clientID, PutDown *message)
{
    //Get currPlayer = iterator(clientID)

    //currPlayer.putDown();

    //Send UpdateScore to currPlayer
}
void GoFishServer::handle(int clientID, Ask *message)
{
    //Get currPlayer = iterator(clientID)
    //Send AskEventPersonal to currPlayer+1
    //Send AskEvent to everyone but currPlayer and currPlayer+1

    //Check currPlayer+1 amountOf(message->Rank)

    //if > 0
        //Send AskEvent_Size to everyone but currPlayer and currPlayer+1
        //currPlayer.addCards(Query currPlayer+1)
        //ReceiveCards currPlayer

    //else
        //Send AskEvent_GoFish to everyone but currPlayer and currPlayer+1
        //Card temp = Pool.deal();
        //currPlayer.add(temp);
        //Send AskEvent_ReceiveFish to currPlayer
}
void GoFishServer::handle(int clientID, ReceiveEndTurn *message)
{
    //Broadcast EndTurn to all Players
    //UpdateScore for clientID
}

