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
#include "nim.h"
#include "../game/game.h"
#include "../game/abstractplayer.h"
#include <string.h>
#include <iostream>
#include <ctime>
#include <QApplication>
#include "../client_GUI/nim_gui.h"
#include <thread>
#include "../NimServer/nimserver.h"
#include <condition_variable>

Nim::Nim(Socket * sock) : Game(sock)
{
    gameNotOver = true;
    opponentMoveReceived = false;
    log = new vector<std::string>();
    objects->addToEnd(GameObject(1));
    objects->addToEnd(GameObject(2));
    objects->addToEnd(GameObject(1));


}

void Nim::run()
{
    cout << "calling Nim::run" << endl;
    gui = new Nim_GUI();
    gui->show();
    log->push_back("Started game.");
    gui->refresh_screen(0, objects->size(),log,"You",true);

     //check server for who starts
    waitForOpponent();
    if(startingPlayer)
        makeMove();

    while(gameNotOver){

        if(checkForGameOver())
            break;
    // send PlayerRemovedItems message with removeNum
        // wait for opponent's move
        waitForOpponent();
        gui->refresh_screen(0, objects->size(),log,"Opponent",true);
        if(checkForGameOver())
                break;
        makeMove();
    }

}

void Nim::makeMove()
{
      int removeNum;



    while(gui->moved == false)
    {
        wait(5000);

    }
    removeNum = gui->get_input();
    gui->refresh_screen(0, objects->size(),log,"Opponent",false);
    socket->send(new PlayerRemovedItems(removeNum));
}

bool Nim::checkForGameOver()
{

    if(objects->size() < 2){
       gameNotOver = false;
       return true;
    }
    return false;
}

void Nim::gameOver(){
    std::cout << "Game Over." << std::endl;
}

void Nim::waitForOpponent()
{
    //std::cout << "Waiting for opponent..." << std::endl;
    while(!opponentMoveReceived)
    {
    wait(5000);

    opponentMoveReceived = true;  // REMOVE WHEN SERVER WORKS
    }
    opponentMoveReceived = false;
}
/**
 * @brief Waits for the given number of milliseconds(taken from cplusplus forum).
 * @param milliseconds that you want to wait.
 */
void Nim::wait( int units)
{

    clock_t start_time = clock();
    clock_t end_time = units * 1000 + start_time;
    while(clock() != end_time) {}
}

/**
 * @brief Handles how to receive a message saying how many items the player removed.
 * @param message received from server saying a player removed items.
 */
void Nim::handle(PlayerRemovedItems * message)
{


    objects->deal(message->number);
    log->push_back("Opponent removed " + message->number);
    opponentMoveReceived = true;
}

void Nim::handle(PlayerTurn * message)
{
    std::cout << "handling playerturn\n";
    opponentMoveReceived = true;
    if(message->number == 1)
        startingPlayer = true;
    else
        startingPlayer = false;

    run();
}
