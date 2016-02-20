#ifndef MESSAGEFORMAT_H
#define MESSAGEFORMAT_H

#include "format.h"
#include "formatutils.h"
#include "message.h"
#include "messagetype.h"

template<typename T>
struct Format<T *, typename std::enable_if<std::is_base_of<Message<T>, T>::value, void>::type> {
    static int formatSize(const T * const *source);
    static void formatRead(char *&source, T **dest);
    static void formatWrite(char *&dest, const T * const *source);
};

template<typename T>
int Format<T *, typename std::enable_if<std::is_base_of<Message<T>, T>::value, void>::type>::formatSize(const T * const *source) {
    MessageType messageType = MessageToEnum<T>::Enum;
    int messageSize = (*source)->size();
    return Formats::size(&messageType) + Formats::size(&messageSize) + messageSize;
}

template<typename T>
void Format<T *, typename std::enable_if<std::is_base_of<Message<T>, T>::value, void>::type>::formatRead(char *& source, T **dest) {
    MessageType messageType;
    int messageSize;
    Formats::read(source, &messageType, &messageSize);
    *dest = Message<T>::read(source);
}

template<typename T>
void Format<T *, typename std::enable_if<std::is_base_of<Message<T>, T>::value, void>::type>::formatWrite(char *& dest, const T * const *source) {
    MessageType messageType = MessageToEnum<T>::Enum;
    int messageSize = (*source)->size();
    Formats::write(dest, &messageType, &messageSize);
    (*source)->write(dest);
}

#endif // MESSAGEFORMAT_H
