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
#include "game.h"
#include "abstractplayer.h"
#include <string>
/**
 * @brief Game::Game instantiates GameObjectContainer and players vector
 */
Game::Game()
{
    objects = new GameObjectContainer();
    players = new std::vector<AbstractPlayer>();
    //gServer = new GameServer();
}
Game::Game(Socket *client_socket)
{
    objects = new GameObjectContainer();
    players = new std::vector<AbstractPlayer>();

    socket = client_socket;

    socket->setHandler(this);
}

/**
 * @brief Handles receiving a game over message from the server
 * @param message received from the server indicating the game is over
 */
void Game::handle(GameOver * message)
{
    // trigger game over events
    // send GameOverSuccess if successful or GameOverFailure if not

}
/**
 * @brief Handles receiving a game start message from the server by calling the run method.
 * @param message from server indicating the game is starting
 */
void Game::handle(GameStart * message)
{

    // send GameStartSuccess message if successful or GameStartFailure if not
}
void Game::handle(ChatIncoming *message){
    emit passChatMessage(message);
}

Game::~Game()
{
    delete objects;
    delete players;
}
