#ifndef CLIENTGUI_MESSAGE_H
#define CLIENTGUI_MESSAGE_H

#include "../server/format.h"
#include "../server/formatutils.h"
#include "../server/message.h"
#include "../server/vectorformat.h"
#include <string>
#include <vector>



/**
 * @brief Informs Players who the game begins with.
 */
/**
 * @brief The UpdateLobby class
 * Update each user's lobby list to show all current players in it
 */
class UpdateLobby : public Message<UpdateLobby> {
public:
    UpdateLobby(std::vector<std::string> playerlist) : playerlist(playerlist) { }

    int size() const { return Formats::size(&playerlist); }
    void write(char *& dest) const { Formats::write(dest, &playerlist); }

    std::vector<std::string> playerlist;

    static UpdateLobby * implRead(char *&source) { return new UpdateLobby(Formats::read<std::vector<std::string>>(source)); }
};

/**
 * @brief The HostLobby class
 * When host chooses a game and clicks host. Create a lobby.
 */
class HostLobby : public Message<HostLobby> {
public:
    HostLobby(std::string hostname, std::string gameName) : hostname(hostname), gameName(gameName) { }

    int size() const { return Formats::size(&hostname, &gameName); }
    void write(char *& dest) const { Formats::write(dest, &hostname, &gameName); }

    std::string hostname, gameName;

    static HostLobby * implRead(char *&source) { return new HostLobby(Formats::read<std::string>(source), Formats::read<std::string>(source)); }
};
/**
 * @brief The CloseLobby class
 * When host clicks "abandon lobby"; closes the lobby.
 */
class CloseLobby : public Message<CloseLobby> {
public:
    CloseLobby(std::string hostname) : hostname(hostname) { }

    int size() const { return Formats::size(&hostname); }
    void write(char *& dest) const { Formats::write(dest, &hostname); }

    std::string hostname;

    static CloseLobby * implRead(char *&source) { return new CloseLobby(Formats::read<std::string>(source)); }
};


class ChatInput : public Message<ChatInput> {
public:
    ChatInput(std::string chatString) : chatString(chatString) { }

    int size() const { return Formats::size(&chatString); }
    void write(char *& dest) const { Formats::write(dest, &chatString); }

    std::string chatString;

    static ChatInput * implRead(char *&source) { return new ChatInput(Formats::read<std::string>(source)); }
};



class ChatIncoming : public Message<ChatIncoming> {
public:
    ChatIncoming(std::string chatString) : chatString(chatString) { }

    int size() const { return Formats::size(&chatString); }
    void write(char *& dest) const { Formats::write(dest, &chatString); }

    std::string chatString;

    static ChatIncoming * implRead(char *&source) { return new ChatIncoming(Formats::read<std::string>(source)); }
};


class NimInput : public Message<NimInput> {
public:
    NimInput(int stoneTaken, std::string msg) : stoneTaken(stoneTaken), msg(msg) { }

    int size() const { return Formats::size(&stoneTaken, &msg); }
    void write(char *& dest) const { Formats::write(dest, &stoneTaken, &msg); }

    int stoneTaken; std::string msg;

    static NimInput * implRead(char *&source) { return new NimInput(Formats::read<int>(source), Formats::read<std::string>(source)); }
};


class NimIncoming : public Message<NimIncoming> {
public:
    NimIncoming(int stoneTaken,std::string msg) : stoneTaken(stoneTaken), msg(msg) { }

    int size() const { return Formats::size(&stoneTaken, &msg); }
    void write(char *& dest) const { Formats::write(dest, &stoneTaken, &msg); }

    int stoneTaken; std::string msg;

    static NimIncoming * implRead(char *&source) { return new NimIncoming(Formats::read<int>(source), Formats::read<std::string>(source)); }
};





#endif // CLIENTGUI_MESSAGE_H
