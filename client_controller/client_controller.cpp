#include "client_controller.h"
#include "../client_GUI/client_gui.h"

ClientController::ClientController()
{
    // start the gui
    clientGUI = new client_GUI();

    clientGUI->show();

}

ClientController::~ClientController(){
    delete clientGUI;
}

void ClientController::receiveName(std::__1::string name){
    playerName = name;
}

void ClientController::receiveHostDecision(bool wantsToHost){
    isHosting = wantsToHost;
}

void ClientController::receiveIP(std::__1::string ip){
    ipToConnectTo = ip;
}

