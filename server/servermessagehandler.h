#ifndef SERVERMESSAGEHANDLER_H
#define SERVERMESSAGEHANDLER_H

#include <iostream>
#include <typeinfo>
#include "clientid.h"
#include "message.h"
#include "messagetype.h"
#include "messages.h"
#include "../client_GUI/clientgui_message.h"
#include "../Nim/nim_messages.h"
//#include "../GoFishClient/gfclientmess.h"
#include "../GoFishServer/gfservermess.h"

#define SERVER_HANDLE(MESSAGE) \
    virtual void handle(ClientID, MESSAGE *) { std::cout << "<ServerMessageHandler>: Base handler called..." << std::endl; }

class ServerMessageHandler {
public:
    virtual ~ServerMessageHandler() { }

    SERVER_HANDLE(Ping)
    SERVER_HANDLE(JoinLobby)
    SERVER_HANDLE(JoinLobbySuccess)
    SERVER_HANDLE(JoinLobbyFailure)
    SERVER_HANDLE(GameStart)
    SERVER_HANDLE(GameStartSuccess)
    SERVER_HANDLE(GameStartFailure)
    SERVER_HANDLE(GameOver)
    SERVER_HANDLE(GameOverSuccess)
    SERVER_HANDLE(GameOverFailure)
    SERVER_HANDLE(UpdateLobby)
    SERVER_HANDLE(ChatInput)
    SERVER_HANDLE(ChatIncoming)
    SERVER_HANDLE(NimInput)
    SERVER_HANDLE(NimIncoming)
    SERVER_HANDLE(PlayerTurn)
    SERVER_HANDLE(PlayerRemovedItems)
    SERVER_HANDLE(ReceiveEndTurn)
    SERVER_HANDLE(Ask)
    SERVER_HANDLE(PutDown)
    SERVER_HANDLE(PlayerList)

    template<typename T>
    void handleTemplate(ClientID client, T *message) {
        std::cout << "Server received message type " << typeid(T).name() << " from client " << client << std::endl;
        this->handle(client, message);
    }
};
#undef SERVER_HANDLE
#endif // SERVERMESSAGEHANDLER_H
