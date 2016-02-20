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
#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

#include "clientsocket.h"
#include "format.h"
#include "formatutils.h"
#include "messages.h"
#include "messageformat.h"
#include "messagehandler.h"
#include "messagetype.h"
#include "servermessagehandler.h"
#include "serversocket.h"
#include "vectorformat.h"

ServerSocket *server;
Socket *client1, *client2;

std::mutex coutMutex;

class ClientHandler : public MessageHandler {
public:
    ClientHandler(int id) : id(id) { }
    void handle(Ping *);
    void handle(JoinLobbySuccess *);
    void handle(JoinLobbyFailure *);

    const int id;
};

void ClientHandler::handle(Ping *) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "Client " << id << " received: Ping()" << std::endl;
}
void ClientHandler::handle(JoinLobbySuccess *) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "Client " << id << " received: JoinLobbySuccess()" << std::endl;
}
void ClientHandler::handle(JoinLobbyFailure *message) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "Client " << id << " received: JoinLobbyFailure(" << message->error << ")" << std::endl;
}

class ServerHandler : public ServerMessageHandler {
public:
    ServerHandler(int id) : serverID(id) { }
    void handle(ClientID, JoinLobby *);

    const int serverID;
};

void ServerHandler::handle(ClientID id, JoinLobby *message) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "Server " << serverID << " recevied from client " << id << ": " << "JoinLobby(" << message->username << ")" << std::endl;
    if (id % 2) {
        server->send(id, new JoinLobbySuccess("foo"));
    } else {
        server->send(id, new JoinLobbyFailure("Server is unhappy with you!"));
    }
}

int main() {
    /*char *buffer;

    JoinLobby *msg = new JoinLobby("meow meow meow meow");

    int len = Formats::serialize(&buffer, &msg);
    std::cout << "message: serialized " << len << " bytes" << std::endl;

    JoinLobby *copy;
    Formats::read(buffer, &copy);

    char *vecbuf;

    std::vector<int> vec = {1, 2, 3, 4, 5};

    int veclen = Formats::serialize(&vecbuf, &vec);
    std::cout << "vector: serialized " << veclen << " bytes" << std::endl;

    std::vector<int> newvec;
    Formats::read(vecbuf, &newvec);*/

    int port = 9001;

    server = new ServerSocket(port, new ServerHandler(1));
    server->listen();

    client1 = new Socket("127.0.0.1", port, new ClientHandler(1));
    client1->connect();
    client2 = new Socket("127.0.0.1", port, new ClientHandler(2));
    client2->connect();

    client1->send(new JoinLobby("foo"));
    client2->send(new JoinLobby("nobody"));

    std::this_thread::sleep_for(std::chrono::duration<int>(1));

    server->broadcast(new Ping());

    std::this_thread::sleep_for(std::chrono::duration<int>(1));

    server->setHandler(new ServerHandler(2));

    std::this_thread::sleep_for(std::chrono::duration<int>(1));

    client1->setHandler(new ClientHandler(3));
    client2->setHandler(new ClientHandler(4));

    client1->send(new JoinLobby("bar"));
    client2->send(new JoinLobby("somebody"));

    std::this_thread::sleep_for(std::chrono::duration<int>(2));

    client1->disconnect();
    std::cout << "Client 1 disconnected" << std::endl;
    client2->disconnect();
    std::cout << "Client 2 disconnected" << std::endl;

    server->close();
    std::cout << "Server closed" << std::endl;

    return 0;
}

