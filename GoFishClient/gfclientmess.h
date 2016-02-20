#ifndef GFCLIENTMESS
#define GFCLIENTMESS

#include "../server/format.h"
#include "../server/formatutils.h"
#include "../server/message.h"
#include "../server/vectorformat.h"
#include "../GoFish/player.h"
#include <string>
#include <vector>

/**
 * @brief Informs Players who the game begins with.
 */
class StartingPlayer : public Message<StartingPlayer> {
public:
    StartingPlayer(int clientID) : clientID(clientID) { }

    int size() const { return Formats::size(&clientID); }
    void write(char *& dest) const { Formats::write(dest, &clientID); }

    const int clientID;

    static StartingPlayer * implRead(char *&source) { return new StartingPlayer(Formats::read<int>(source)); }
};

class TurnEnd : public Message<TurnEnd> {
public:
    TurnEnd(bool b) : b(b) { }

    int size() const { return Formats::size(&b); }
    void write(char *& dest) const { Formats::write(dest, &b); }

    const int b;

    static TurnEnd * implRead(char *&source) { return new TurnEnd(Formats::read<bool>(source)); }
};

class AllPlayers : public Message<AllPlayers> {
public:
    AllPlayers(std::vector<Player> thesePlayers) : thesePlayers(thesePlayers) { }

    int size() const { return Formats::size(&thesePlayers); }
    void write(char *& dest) const { Formats::write(dest, &thesePlayers); }

    std::vector<Player> thesePlayers;

    static AllPlayers * implRead(char *&source) { return new AllPlayers(Formats::read<std::vector<Player>>(source)); }
};

class ReceiveHand : public Message<ReceiveHand> {
public:
    ReceiveHand(std::vector<Card> Hand) : Hand(Hand) { }

    int size() const { return Formats::size(&Hand); }
    void write(char *& dest) const { Formats::write(dest, &Hand); }

    std::vector<Card> Hand;

    static ReceiveHand * implRead(char *&source) { return new ReceiveHand(Formats::read<std::vector<Card>>(source)); }
};

class ReceiveCards : public Message<ReceiveCards> {
public:
    ReceiveCards(std::vector<Card> Cards) : Cards(Cards) { }

    int size() const { return Formats::size(&Cards); }
    void write(char *& dest) const { Formats::write(dest, &Cards); }

    std::vector<Card> Cards;

    static ReceiveCards * implRead(char *&source) { return new ReceiveCards(Formats::read<std::vector<Card>>(source)); }
};

class AskEventPersonal : public Message<AskEventPersonal> {
public:
    AskEventPersonal(int askRank) : askRank(askRank) { }

    int size() const { return Formats::size(&askRank); }
    void write(char *& dest) const { Formats::write(dest, &askRank); }

    int askRank;

    static AskEventPersonal * implRead(char *&source) { return new AskEventPersonal(Formats::read<int>(source)); }
};

class AskEvent : public Message<AskEvent> {
public:
    AskEvent(int askRank) : askRank(askRank) { }

    int size() const { return Formats::size(&askRank); }
    void write(char *& dest) const { Formats::write(dest, &askRank); }

    int askRank;

    static AskEvent * implRead(char *&source) { return new AskEvent(Formats::read<int>(source)); }
};

class AskEvent_Size : public Message<AskEvent_Size> {
public:
    AskEvent_Size(int Size) : Size(Size) { }

    int size() const { return Formats::size(&Size); }
    void write(char *& dest) const { Formats::write(dest, &Size); }

    int Size;

    static AskEvent_Size * implRead(char *&source) { return new AskEvent_Size(Formats::read<int>(source)); }
};

class AskEvent_Fish : public Message<AskEvent_Fish> {
public:
    AskEvent_Fish(bool b) : b(b) { }

    int size() const { return Formats::size(&b); }
    void write(char *& dest) const { Formats::write(dest, &b); }

    bool b;

    static AskEvent_Fish * implRead(char *&source) { return new AskEvent_Fish(Formats::read<bool>(source)); }
};

class ReceiveWinString : public Message<ReceiveWinString> {
public:
    ReceiveWinString(std::string winString) : winString(winString) { }

    int size() const { return Formats::size(&winString); }
    void write(char *& dest) const { Formats::write(dest, &winString); }

    std::string winString;

    static ReceiveWinString * implRead(char *&source) { return new ReceiveWinString(Formats::read<std::string>(source)); }
};

class UpdateHand : public Message<UpdateHand> {
public:
    UpdateHand(std::vector<Card> Hand) : Hand(Hand) { }

    int size() const { return Formats::size(&Hand); }
    void write(char *& dest) const { Formats::write(dest, &Hand); }

    std::vector<Card> Hand;

    static UpdateHand * implRead(char *&source) { return new UpdateHand(Formats::read<std::vector<Card>>(source)); }
};

class UpdateScore : public Message<UpdateScore> {
public:
    UpdateScore(int Score) : Score(Score) { }

    int size() const { return Formats::size(&Score); }
    void write(char *& dest) const { Formats::write(dest, &Score); }

    int Score;

    static UpdateScore * implRead(char *&source) { return new UpdateScore(Formats::read<int>(source)); }
};

class ReceiveFish : public Message<ReceiveFish> {
public:
    ReceiveFish(Card Fish) : Fish(Fish) { }

    int size() const { return Formats::size(&Fish); }
    void write(char *& dest) const { Formats::write(dest, &Fish); }

    Card Fish;

    static ReceiveFish * implRead(char *&source) { return new ReceiveFish(Formats::read<Card>(source)); }
};


#endif // GFCLIENTMESS
