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
#include "gameserver.h"
#include "../client_GUI/clientgui_message.h"

GameServer::GameServer()
{
    //Nothing, need it in order to extend
}

GameServer::GameServer(int port)
{
    //turnNum = 0;
    player = std::vector<ClientID>();
    socket = new ServerSocket(port,this);
    socket->listen();
}
/*
int GameServer::getTurn()
{
    turnNum++;
    return turnNum-1;
}
*/
bool GameServer::gameOver()
{

}

void GameServer::handle(ClientID client, GameStart * message)
{

    // broadcast GameStart
}

void GameServer::handle(ClientID client, GameStartFailure * message)
{
    // broadcast username of user who was unable to start the game
}

void GameServer::handle(ClientID client, GameStartSuccess * message)
{
    // do nothing
}

void GameServer::handle(ClientID client, GameOver * message)
{
    // broadcast game over
}

void GameServer::handle(ClientID client, GameOverFailure * message)
{
    // broadcast user who rage quit
}

void GameServer::handle(ClientID client, GameOverSuccess * message)
{
    // do nothing (keep track of users to make sure everyone was successful?)
}

void GameServer::handle(ClientID client, JoinLobby *message)
{
    player.push_back(client);
    userNameMap[client] = message->username;
    std::vector<std::string> v;
    for(std::map<ClientID,std::string>::iterator it = userNameMap.begin(); it != userNameMap.end(); ++it )
    {
        v.push_back(it->second);
    }
    socket->send(client, new JoinLobbySuccess("Nim"));
    socket->broadcast(new UpdateLobby(v));
    std::cout << message->username << std::endl;
}

void GameServer::handle(ClientID client, ChatInput *message)
{
    std::cout << "preparing to broadcast chat" << endl;
    socket->broadcast(new ChatIncoming(message->chatString));
}

void GameServer::handle(ClientID client, NimInput *message)
{
    std::cout << "preparing to broadcast nim" << endl;
    socket->broadcast(new NimIncoming(message->stoneTaken, message->stoneRemain, message->msg, message->turn));
}
void GameServer::startGame()
{
    for(std::map<ClientID,std::string>::iterator it = userNameMap.begin(); it != userNameMap.end(); ++it )
    {
        if(it == userNameMap.begin())
            socket->send(it->first,new PlayerTurn(1));
        else
        socket->send(it->first, new PlayerTurn(0));
    }
}

    GameServer::~GameServer(){
    delete socket;
}
