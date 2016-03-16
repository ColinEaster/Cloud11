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
#include <algorithm> // for find

Nim::Nim(Socket * sock) : Game(sock)
{
    gameNotOver = true;

    amountsThatCanBeRemoved.push_back(1);
    amountsThatCanBeRemoved.push_back(2);



}

Nim::Nim(Socket *client_socket, std::vector<std::string> playerList, std::string playerName, bool hosting): Game(client_socket){
    gameNotOver = true;
    yourTurn = hosting;

    amountsThatCanBeRemoved.push_back(1);
    amountsThatCanBeRemoved.push_back(2);
    this->playerName = playerName;
    std::remove(playerList.begin(), playerList.end(), playerName);
    opponentName = playerList[0];

}

void Nim::receiveUserWantsToRemoveStones(int numberOfStonesRemoved){
    // check if your turn?
    if(checkIfNumberOfStonesIsValid(numberOfStonesRemoved)){
        emit allowInput(opponentName, false);
        NimInput* message = new NimInput(numberOfStonesRemoved, "" );
        socket->send(message);
        delete message;

    }
    else {
        emit displayMessage(Error_Message);
        emit allowInput(playerName, true);
    }
}

void Nim::startGame(){
    if(yourTurn)
    emit allowInput(playerName,yourTurn);
    else
    emit allowInput(opponentName,yourTurn);
}

void Nim::nimIncomingMessageReceived(int stonesTaken){
    numStones -= stonesTaken;
    emit displayMessage(stonesTaken + ": stone(s) were taken.");
    emit displayStones(numStones);
    if(numStones < *std::min_element(amountsThatCanBeRemoved.begin(),amountsThatCanBeRemoved.end()))
        endTheGame();

    if(yourTurn){
        yourTurn = false;
        emit allowInput(opponentName, yourTurn);
    }
    else{
        yourTurn = true;
        emit allowInput(playerName, yourTurn);
    }
}

bool Nim::checkIfNumberOfStonesIsValid(const int &num){
    if(std::find(amountsThatCanBeRemoved.begin(),amountsThatCanBeRemoved.end(),num) != amountsThatCanBeRemoved.end())
        return true;

    return false;
}

bool Nim::checkForGameOver()
{

    if(numStones < 2){
       gameNotOver = false;
       return true;
    }
    return false;
}

void Nim::endTheGame(){
    std::cout << "done";
    emit displayMessage("The game is over.");
    emit quitGame();
}

void Nim::gameOver(){
    std::cout << "Game Over." << std::endl;
}



/**
 * @brief Handles how to receive a message saying how many items the player removed.
 * @param message received from server saying a player removed items.
 */
void Nim::handle(PlayerRemovedItems * message)
{


    log.push_back("Opponent removed " + message->number);
    yourTurn = true;
}

void Nim::handle(PlayerTurn * message)
{
    std::cout << "handling playerturn\n";
    yourTurn = true;
    if(message->number == 1)
        startingPlayer = true;
    else
        startingPlayer = false;

}

void Nim::handle(NimIncoming *msg){

    QMetaObject::invokeMethod(this, "nimIncomingMessageReceived", Qt::QueuedConnection, Q_ARG(int, msg->stoneTaken));
    delete msg;
}
