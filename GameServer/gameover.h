#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "../server/format.h"
#include "../server/formatutils.h"
#include "../server/message.h"
#include <string>

/**
 * @brief The GameOver class is a message that lets the clients know the game is over.
 */
class GameOver : public Message<GameOver> {
public:
    GameOver(int over) : over(over) { }

    int size() const { return Formats::size(&over); }
    void write(char *& dest) const { Formats::write(dest, &over); }

    const int over;

    static GameOver * implRead(char *&source) { return new GameOver(Formats::read<int>(source)); }
};

/**
 * @brief The GameOverSuccess class is a message that the clients send back to let the server know they have received the game over message and have ended the game.
 */
class GameOverSuccess : public Message<GameOverSuccess> {
public:
    GameOverSuccess() { }

    int size() const { return 0; }
    void write(char *&) const { }

    static GameOverSuccess * implRead(char *&) { return new GameOverSuccess(); }
};
/**
 * @brief The GameOverFailure class is a message that the clients send back to let the server know they have failed to end the game after receiving a game over message.
 */
class GameOverFailure : public Message<GameOverFailure> {
public:
    GameOverFailure(std::string error) : error(error) { }

    int size() const { return Formats::size(&error); }
    void write(char *&dest) const { Formats::write(dest, &error); }

    const std::string error;

    static GameOverFailure * implRead(char *&source) { return new GameOverFailure(Formats::read<std::string>(source)); }
};


#endif // GAMEOVER_H
