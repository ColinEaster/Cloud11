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
#include <arpa/inet.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>

#include "serversocket.h"

int ServerSocket::nextClientID = 1;

ServerSocket::ServerSocket(int port, ServerMessageHandler *handler) : port(port), handler(handler) {
    sockfd = -1;
    bound = false;
}

ServerSocket::~ServerSocket() {
    if (bound) close();
}

void ServerSocket::setHandler(ServerMessageHandler *h) {
    handler = h;
    std::vector<std::thread *> workers;
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto &client : clients) {
        workers.push_back(new std::thread(&ServerSocket::setClientHandler, client.second, new HandlerAdapter(client.first, h)));
    }
    for (std::thread *t : workers) {
        t->join();
    }
}

void ServerSocket::listen() {
    if (bound) {
        std::cerr << "Server socket already bound" << std::endl;
        return;
    }

    struct sockaddr_in sockaddr;
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(port);

    if (::bind(sockfd, (struct sockaddr *) &sockaddr, sizeof(sockaddr))) {
        //TODO: error handling
        std::cerr << "Server socket bind sad! :(" << std::endl;
        return;
    }
    if (::listen(sockfd, 5)) {
        //TODO: error handling
        std::cerr << "Server socket listen sad! :(" << std::endl;
        return;
    }

    bound = true;

    std::thread(&ServerSocket::listenerLoop, this).detach();
}

void ServerSocket::close() {
    if (!bound) {
        std::cerr << "Server socket already unbound" << std::endl;
        return;
    }

    bound = false;
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto &client : clients) {
        delete client.second;
    }

    shutdown(sockfd, SHUT_RDWR);
    ::close(sockfd);
}

void ServerSocket::setClientHandler(Socket *sock, MessageHandler *h) {
    MessageHandler *prev = sock->handler;
    sock->setHandler(h);
    delete prev;
}

void ServerSocket::listenerLoop() {
    while (bound) {
        struct sockaddr_in clientaddr;
        socklen_t clientaddrSize = sizeof(clientaddr);
        int clientsockfd = accept(sockfd, (struct sockaddr *) &clientaddr, &clientaddrSize);
        if (clientsockfd == -1) {
            std::cerr << "Server socket accept sad! :(" << std::endl;
            return;
        }
        int id = nextClientID++;
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients[id] = new Socket(clientsockfd, new HandlerAdapter(id, handler));
    }
}
