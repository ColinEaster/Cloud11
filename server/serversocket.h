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

#define HANDLE_MESSAGE(MESSAGE) \
    virtual void handle(MESSAGE *message) { serverHandler->handleTemplate(client, message); }

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
        HANDLE_MESSAGE(Ping)
        HANDLE_MESSAGE(JoinLobby)
        HANDLE_MESSAGE(JoinLobbySuccess)
        HANDLE_MESSAGE(JoinLobbyFailure)
        HANDLE_MESSAGE(GameStart)
        HANDLE_MESSAGE(GameStartSuccess)
        HANDLE_MESSAGE(GameStartFailure)
        HANDLE_MESSAGE(GameOver)
        HANDLE_MESSAGE(GameOverSuccess)
        HANDLE_MESSAGE(GameOverFailure)
        HANDLE_MESSAGE(UpdateLobby)
        HANDLE_MESSAGE(ChatInput)
        HANDLE_MESSAGE(ChatIncoming)
        HANDLE_MESSAGE(NimInput)
        HANDLE_MESSAGE(NimIncoming)
        HANDLE_MESSAGE(PlayerRemovedItems)
        HANDLE_MESSAGE(PlayerTurn)
        HANDLE_MESSAGE(ReceiveEndTurn)
        HANDLE_MESSAGE(Ask)
        HANDLE_MESSAGE(PutDown)
        HANDLE_MESSAGE(PlayerList)

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
#undef HANDLE_MESSAGE
#endif // SERVERSOCKET_H
