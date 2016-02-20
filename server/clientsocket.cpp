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
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "clientsocket.h"

Socket::Socket(const char *hostname, int port, MessageHandler *handler) : hostname(hostname), port(port), handler(handler) {
    sockfd = -1;
    connected = false;
    handlerSwapping = false;
    activeProcessingCount = 0;
}

Socket::Socket(int sockfd, MessageHandler *handler) : hostname("local"), port(-1), handler(handler), sockfd(sockfd) {
    connected = true;
    handlerSwapping = false;
    activeProcessingCount = 0;
    startThreads();
}

Socket::~Socket() {
    if (connected) disconnect();
}

void Socket::setHandler(MessageHandler *h) {
    handlerSwapping = true;

    std::unique_lock<std::mutex> lock(handlerSwapMutex);
    while (activeProcessingCount > 0) handlerSwapCondition.wait(lock);
    lock.unlock();

    handler = h;

    handlerSwapping = false;
    handlerSwapProcessingCondition.notify_all();
}

void Socket::connect() {
    if (connected) {
        std::cerr << "Socket already connected" << std::endl;
        return;
    }

    struct sockaddr_in sockaddr;
    //std::cout << "Read message\n";
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    inet_pton(AF_INET, hostname, &sockaddr.sin_addr);
    sockaddr.sin_port = htons(port);

    if (::connect(sockfd, (struct sockaddr *) &sockaddr, sizeof(sockaddr))) {
        //TODO: error handling
        std::cerr << "Socket connect sad! :(" << std::endl;
        return;
    }

    connected = true;

    startThreads();
}

void Socket::disconnect() {
    if (!connected) {
        std::cerr << "Socket already disconnected" << std::endl;
        return;
    }

    connected = false;
    processingCondition.notify_all();

    for (std::thread *worker : workers) {
        worker->join();
        delete worker;
    }

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}

void Socket::startThreads() {
    readThread = std::thread(&Socket::readLoop, this);
    readThread.detach();
    for (int i = 0; i < processingThreadPoolSize; ++i) {
        workers.push_back(new std::thread(&Socket::processingLoop, this));
    }
}

void Socket::readLoop() {
    while (connected) {
        char *buffer = readMessage();
        if (buffer) {
            std::unique_lock<std::mutex> lock(processingMutex);
            processingQueue.push_back(buffer);
            lock.unlock();
            processingCondition.notify_one();
        }
    }
}

void Socket::processingLoop() {
    while (connected) {
        std::unique_lock<std::mutex> lock(processingMutex);
        while (connected && processingQueue.empty()) processingCondition.wait(lock);

        if (connected) {
            char *buffer = processingQueue.back();
            processingQueue.pop_back();
            lock.unlock();

            std::unique_lock<std::mutex> handlerLock(handlerSwapMutex);
            while (handlerSwapping) handlerSwapProcessingCondition.wait(handlerLock);
            handlerLock.unlock();

            activeProcessingCount++;

            processMessage(buffer);
            free(buffer);

            activeProcessingCount--;
            handlerSwapCondition.notify_all();
        } else {
            lock.unlock();
        }
    }
}

char * Socket::readMessage() {
    MessageType messageType;
    int messageSize;
    int headerSize = Formats::size(&messageType, &messageSize);

    char *header = (char *) malloc(headerSize);

    int totalRead = 0;
    do {
        int readcount = read(sockfd, header + totalRead, headerSize - totalRead);
        if (readcount < 0) {
            //TODO: error handling
            if (connected) std::cerr << "Socket read sad! :(" << std::endl;
            return nullptr;
        }
        totalRead += readcount;
    } while (totalRead < headerSize);

    char *tempHeader = header;
    Formats::read(tempHeader, &messageType, &messageSize);

    char *messageBuffer = (char *) realloc(header, headerSize + messageSize);
    char *tempMessage = messageBuffer + headerSize;

    while (messageSize > 0) {
        int readcount = read(sockfd, tempMessage, messageSize);
        if (readcount < 0) {
            //TODO: error handling
            if (connected) std::cerr << "Socket read sad! :(" << std::endl;
            return nullptr;
        }
        tempMessage += readcount;
        messageSize -= readcount;
    }

    return messageBuffer;
}

void Socket::processMessage(char *buffer) {
    char *temp = buffer;
    MessageType type;
    Formats::read(temp, &type);
    messageHelper<ENUM_LAST>(type, buffer);
}
