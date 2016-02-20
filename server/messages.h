#ifndef MESSAGES_H
#define MESSAGES_H

#include "format.h"
#include "formatutils.h"
#include "message.h"

class JoinLobby : public Message<JoinLobby> {
public:
    JoinLobby(std::string username) : username(username) { }

    int size() const { return Formats::size(&username); }
    void write(char *& dest) const { Formats::write(dest, &username); }

    const std::string username;

    static JoinLobby * implRead(char *&source) { return new JoinLobby(Formats::read<std::string>(source)); }
};


class JoinLobbySuccess : public Message<JoinLobbySuccess> {
public:
    JoinLobbySuccess(std::string gameType) : gameType(gameType) { }

    int size() const { return Formats::size(&gameType); }
    void write(char *& dest) const { Formats::write(dest, &gameType); }

    const std::string gameType;

    static JoinLobbySuccess * implRead(char *&source) { return new JoinLobbySuccess(Formats::read<std::string>(source)); }
};


class JoinLobbyFailure : public Message<JoinLobbyFailure> {
public:
    JoinLobbyFailure(std::string error) : error(error) { }

    int size() const { return Formats::size(&error); }
    void write(char *&dest) const { Formats::write(dest, &error); }

    const std::string error;

    static JoinLobbyFailure * implRead(char *&source) { return new JoinLobbyFailure(Formats::read<std::string>(source)); }
};

class Ping : public Message<Ping> {
public:
    Ping() { }

    int size() const { return 0; }
    void write(char *&) const { }

    static Ping * implRead(char *&) { return new Ping(); }
};

#endif // MESSAGES_H
