#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

// TODO: File bug report, header falsely named, inclusion did not provide functionality.
#include <functional>
#include <iostream>

#include "messages.h"
#include "../GameServer/gamestart.h"
#include "../GameServer/gameover.h"
#include "../client_GUI/clientgui_message.h"
#include "../Nim/nim_messages.h"
//#include "../GoFishClient/gfclientmess.h"
#include "../GoFishServer/gfservermess.h"

#define HANDLE(MESSAGE) \
    virtual void handle(MESSAGE *) { std::cout << "<MessageHandler>: Wake up, sheeple..." << std::endl; }

class MessageHandler {
public:
    virtual ~MessageHandler() { }

    HANDLE(Ping)
    HANDLE(JoinLobby)
    HANDLE(JoinLobbySuccess)
    HANDLE(JoinLobbyFailure)
    HANDLE(GameStart)
    HANDLE(GameStartSuccess)
    HANDLE(GameStartFailure)
    HANDLE(GameOver)
    HANDLE(GameOverSuccess)
    HANDLE(GameOverFailure)
    HANDLE(UpdateLobby)
    HANDLE(ChatInput)
    HANDLE(ChatIncoming)
    HANDLE(NimInput)
    HANDLE(NimIncoming)
    HANDLE(PlayerRemovedItems)
    HANDLE(PlayerTurn)
    HANDLE(ReceiveEndTurn)
    HANDLE(Ask)
    HANDLE(PutDown)


    template<typename M>
    void handleTemplate(M *message) {
        std::cout << "Socket received message type " << typeid(M).name() << std::endl;
        this->handle(message);
    }
};


#undef HANDLE
#endif // MESSAGEHANDLER_H
