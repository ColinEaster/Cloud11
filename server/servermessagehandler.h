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

#define NEVER_GONNA_GIVE_YOU_UP(LESS_THAN_THREE) \
    virtual void handle(ClientID, LESS_THAN_THREE *) { std::cout << "<ServerMessageHandler>: Wake up, sheeple..." << std::endl; }

class ServerMessageHandler {
public:
    virtual ~ServerMessageHandler() { }

    NEVER_GONNA_GIVE_YOU_UP(Ping)
    NEVER_GONNA_GIVE_YOU_UP(JoinLobby)
    NEVER_GONNA_GIVE_YOU_UP(JoinLobbySuccess)
    NEVER_GONNA_GIVE_YOU_UP(JoinLobbyFailure)
    NEVER_GONNA_GIVE_YOU_UP(GameStart)
    NEVER_GONNA_GIVE_YOU_UP(GameStartSuccess)
    NEVER_GONNA_GIVE_YOU_UP(GameStartFailure)
    NEVER_GONNA_GIVE_YOU_UP(GameOver)
    NEVER_GONNA_GIVE_YOU_UP(GameOverSuccess)
    NEVER_GONNA_GIVE_YOU_UP(GameOverFailure)
    NEVER_GONNA_GIVE_YOU_UP(UpdateLobby)
    NEVER_GONNA_GIVE_YOU_UP(ChatInput)
    NEVER_GONNA_GIVE_YOU_UP(ChatIncoming)
    NEVER_GONNA_GIVE_YOU_UP(NimInput)
    NEVER_GONNA_GIVE_YOU_UP(NimIncoming)
    NEVER_GONNA_GIVE_YOU_UP(PlayerTurn)
    NEVER_GONNA_GIVE_YOU_UP(PlayerRemovedItems)
    NEVER_GONNA_GIVE_YOU_UP(ReceiveEndTurn)
    NEVER_GONNA_GIVE_YOU_UP(Ask)
    NEVER_GONNA_GIVE_YOU_UP(PutDown)

    template<typename T>
    void handleTemplate(ClientID client, T *message) {
        std::cout << "Server received message type " << typeid(T).name() << " from client " << client << std::endl;
        this->handle(client, message);
    }
};

#endif // SERVERMESSAGEHANDLER_H
