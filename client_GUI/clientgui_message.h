#ifndef CLIENTGUI_MESSAGE_H
#define CLIENTGUI_MESSAGE_H

#include "../server/format.h"
#include "../server/formatutils.h"
#include "../server/message.h"
#include "../server/vectorformat.h"
#include <string>
#include <vector>


using namespace std;

/**
 * @brief Informs Players who the game begins with.
 */
/**
 * @brief The UpdateLobby class
 * Update each user's lobby list to show all current players in it
 */
class UpdateLobby : public Message<UpdateLobby> {
public:
    UpdateLobby(vector<string> playerlist) : playerlist(playerlist) { }

    int size() const { return Formats::size(&playerlist); }
    void write(char *& dest) const { Formats::write(dest, &playerlist); }

    vector<string> playerlist;

    static UpdateLobby * implRead(char *&source) { return new UpdateLobby(Formats::read<vector<string>>(source)); }
};

/**
 * @brief The HostLobby class
 * When host chooses a game and clicks host. Create a lobby.
 */
class HostLobby : public Message<HostLobby> {
public:
    HostLobby(string hostname, string gameName) : hostname(hostname), gameName(gameName) { }

    int size() const { return Formats::size(&hostname, &gameName); }
    void write(char *& dest) const { Formats::write(dest, &hostname, &gameName); }

    string hostname, gameName;

    static HostLobby * implRead(char *&source) { return new HostLobby(Formats::read<string>(source), Formats::read<string>(source)); }
};
/**
 * @brief The CloseLobby class
 * When host clicks "abandon lobby"; closes the lobby.
 */
class CloseLobby : public Message<CloseLobby> {
public:
    CloseLobby(string hostname) : hostname(hostname) { }

    int size() const { return Formats::size(&hostname); }
    void write(char *& dest) const { Formats::write(dest, &hostname); }

    string hostname;

    static CloseLobby * implRead(char *&source) { return new CloseLobby(Formats::read<string>(source)); }
};


class ChatInput : public Message<ChatInput> {
public:
    ChatInput(string chatString) : chatString(chatString) { }

    int size() const { return Formats::size(&chatString); }
    void write(char *& dest) const { Formats::write(dest, &chatString); }

    string chatString;

    static ChatInput * implRead(char *&source) { return new ChatInput(Formats::read<string>(source)); }
};



class ChatIncoming : public Message<ChatIncoming> {
public:
    ChatIncoming(string chatString) : chatString(chatString) { }

    int size() const { return Formats::size(&chatString); }
    void write(char *& dest) const { Formats::write(dest, &chatString); }

    string chatString;

    static ChatIncoming * implRead(char *&source) { return new ChatIncoming(Formats::read<string>(source)); }
};


class NimInput : public Message<NimInput> {
public:
    NimInput(int stoneTaken, int stoneRemain, string msg, int turn) : stoneTaken(stoneTaken), stoneRemain(stoneRemain), msg(msg), turn(turn) { }

    int size() const { return Formats::size(&stoneTaken, &stoneRemain, &msg, &turn); }
    void write(char *& dest) const { Formats::write(dest, &stoneTaken, &stoneRemain, &msg, &turn); }

    int stoneTaken; int stoneRemain; string msg; int turn;

    static NimInput * implRead(char *&source) { return new NimInput(Formats::read<int>(source), Formats::read<int>(source), Formats::read<string>(source), Formats::read<int>(source)); }
};


class NimIncoming : public Message<NimIncoming> {
public:
    NimIncoming(int stoneTaken, int stoneRemain, string msg, int turn) : stoneTaken(stoneTaken), stoneRemain(stoneRemain), msg(msg), turn(turn) { }

    int size() const { return Formats::size(&stoneTaken, &stoneRemain, &msg, &turn); }
    void write(char *& dest) const { Formats::write(dest, &stoneTaken, &stoneRemain, &msg, &turn); }

    int stoneTaken; int stoneRemain; string msg; int turn;

    static NimIncoming * implRead(char *&source) { return new NimIncoming(Formats::read<int>(source), Formats::read<int>(source), Formats::read<string>(source), Formats::read<int>(source)); }
};





#endif // CLIENTGUI_MESSAGE_H
