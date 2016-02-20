#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <atomic>
#include <iostream>
#include <map>
#include <mutex>

#include "clientid.h"
#include "clientsocket.h"
#include "messagehandler.h"
#include "servermessagehandler.h"
#include "../GameServer/gamestart.h"
#include "../GameServer/gameover.h"
#include "../client_GUI/clientgui_message.h"
#include "../Nim/nim_messages.h"
//#include "../GoFishClient/gfclientmess.h"
#include "../GoFishServer/gfservermess.h"

#define I_HATE_CPP(HACK) \
    virtual void handle(HACK *message) { serverHandler->handleTemplate(client, message); }

class ServerSocket {
public:
    ServerSocket(int port, ServerMessageHandler *handler);
    ~ServerSocket();

    void setHandler(ServerMessageHandler *h);

    void listen();
    void close();

    template<typename T>
    void send(ClientID client, T *message);
    template<typename T>
    void broadcast(T *message);

private:
    class HandlerAdapter : public MessageHandler {
    public:
        HandlerAdapter(ClientID client, ServerMessageHandler *serverHandler) : client(client), serverHandler(serverHandler) { }
        I_HATE_CPP(Ping)
        I_HATE_CPP(JoinLobby)
        I_HATE_CPP(JoinLobbySuccess)
        I_HATE_CPP(JoinLobbyFailure)
        I_HATE_CPP(GameStart)
        I_HATE_CPP(GameStartSuccess)
        I_HATE_CPP(GameStartFailure)
        I_HATE_CPP(GameOver)
        I_HATE_CPP(GameOverSuccess)
        I_HATE_CPP(GameOverFailure)
        I_HATE_CPP(UpdateLobby)
        I_HATE_CPP(ChatInput)
        I_HATE_CPP(ChatIncoming)
        I_HATE_CPP(NimInput)
        I_HATE_CPP(NimIncoming)
        I_HATE_CPP(PlayerRemovedItems)
        I_HATE_CPP(PlayerTurn)
        I_HATE_CPP(ReceiveEndTurn)
        I_HATE_CPP(Ask)
        I_HATE_CPP(PutDown)
    private:
        const ClientID client;
        ServerMessageHandler *serverHandler;
    };

    static void setClientHandler(Socket *sock, MessageHandler *h);

    void listenerLoop();

    static int nextClientID;

    const int port;
    ServerMessageHandler *handler;

    int sockfd;
    std::atomic<bool> bound;
    std::mutex clientsMutex;
    std::map<ClientID, Socket *> clients;
};

template<typename T>
void ServerSocket::send(ClientID client, T *message) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    clients.at(client)->send(message);
}

template<typename T>
void ServerSocket::broadcast(T *message) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto &client : clients) {
        client.second->send(message);
    }
}

#endif // SERVERSOCKET_H
