#ifndef GAMESTART_H
#define GAMESTART_H

#include "../server/format.h"
#include "../server/formatutils.h"
#include "../server/message.h"
#include <string>

/**
 * @brief The GameStart class is a message that lets the clients know the game is starting.
 */
class GameStart : public Message<GameStart> {
public:
    GameStart(int start) : start(start) { }

    int size() const { return Formats::size(&start); }
    void write(char *& dest) const { Formats::write(dest, &start); }

    const int start;

    static GameStart * implRead(char *&source) { return new GameStart(Formats::read<int>(source)); }
};

/**
 * @brief The GameStartSuccess class is a message that the clients send back to let the server know they have received the game start message and have started the game.
 */
class GameStartSuccess : public Message<GameStartSuccess> {
public:
    GameStartSuccess(std::string gameType) { }

    int size() const { return Formats::size(&gameType); }
    void write(char *& dest) const { Formats::write(dest, &gameType); }

    const std::string gameType;
    static GameStartSuccess * implRead(char *&source) { return new GameStartSuccess(Formats::read<std::string>(source)); }
};
/**
 * @brief The GameStartFailure class is a message that the clients send back to let the server know they have received the game start message but have failed to start the game.
 */
class GameStartFailure : public Message<GameStartFailure> {
public:
    GameStartFailure(std::string error) : error(error) { }

    int size() const { return Formats::size(&error); }
    void write(char *&dest) const { Formats::write(dest, &error); }

    const std::string error;

    static GameStartFailure * implRead(char *&source) { return new GameStartFailure(Formats::read<std::string>(source)); }
};

/**
 * @brief A message that lets the clients if it is their turn or not.
 */
class PlayerTurn : public Message<PlayerTurn> {
public:
    PlayerTurn(int number) : number(number) { }

    int size() const { return Formats::size(&number); }
    void write(char *& dest) const { Formats::write(dest, &number); }

    const int number;

    static PlayerTurn * implRead(char *&source) { return new PlayerTurn(Formats::read<int>(source)); }
};


#endif // GAMESTART_H
