#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <atomic>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <unistd.h>

#include "formatutils.h"
#include "messageformat.h"
#include "messagehandler.h"
#include "messagetype.h"

class Socket {
    friend class ServerSocket;

public:
    Socket(const char *hostname, int port, MessageHandler *handler);
    Socket(int sockfd, MessageHandler *handler);
    ~Socket();

    void setHandler(MessageHandler *h);

    void connect();
    void disconnect();

    template<typename T>
    void send(T *message);

private:
    void startThreads();

    void readLoop();
    void processingLoop();

    char * readMessage();
    void processMessage(char *buffer);

    template<int N>
    void messageHelper(MessageType m, char *buffer);

    const char *hostname;
    const int port;
    MessageHandler *handler;

    int sockfd;
    std::atomic<bool> connected;

    std::thread readThread;

    std::vector<std::thread *> workers;
    std::mutex processingMutex;
    std::condition_variable processingCondition;
    std::vector<char *> processingQueue;

    std::atomic<bool> handlerSwapping;
    std::atomic<int> activeProcessingCount;
    std::mutex handlerSwapMutex;
    std::condition_variable handlerSwapCondition, handlerSwapProcessingCondition;

    static constexpr int processingThreadPoolSize = 8;
};

template<typename T>
void Socket::send(T *message) {
    char *buffer;
    int size = Formats::serialize<T *>(&buffer, &message);
    char *tempBuffer = buffer;
    do {
        int written = write(sockfd, tempBuffer, size);
        if (written < 0) {
            //TODO: error handling
            if (connected) std::cerr << "Socket write sad! :(" << std::endl;
            return;
        }
        tempBuffer += written;
        size -= written;
    } while (size > 0);
    free(buffer);
}

template<int N>
inline void Socket::messageHelper(MessageType m, char *buffer) {
    if (MessageMapping<N>::Result::Enum == m) {
        typedef typename MessageMapping<N>::Result::Type M;
        M *message;
        Formats::read(buffer, &message);
        handler->handleTemplate(message);
    } else {
        messageHelper<N-1>(m, buffer);
    }
}

template<>
inline void Socket::messageHelper<ENUM_FIRST-1>(MessageType, char *) { }

#endif // CLIENTSOCKET_H
