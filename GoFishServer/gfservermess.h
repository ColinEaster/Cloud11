#ifndef GFSERVERMESS
#define GFSERVERMESS

#include "../server/format.h"
#include "../server/formatutils.h"
#include "../server/message.h"
#include "../server/vectorformat.h"
#include "../GoFish/player.h"
#include <string>
#include <vector>

class PutDown : public Message<PutDown> {
public:
    PutDown(int rank) : rank(rank) { }

    int size() const { return Formats::size(&rank); }
    void write(char *& dest) const { Formats::write(dest, &rank); }

    const int rank;

    static PutDown * implRead(char *&source) { return new PutDown(Formats::read<int>(source)); }
};

class Ask : public Message<Ask> {
public:
    Ask(int rank) : rank(rank) { }

    int size() const { return Formats::size(&rank); }
    void write(char *& dest) const { Formats::write(dest, &rank); }

    const int rank;

    static Ask * implRead(char *&source) { return new Ask(Formats::read<int>(source)); }
};

class ReceiveEndTurn : public Message<ReceiveEndTurn> {
public:
    ReceiveEndTurn() { }

    int size() const { return 0; }
    void write(char *&) const { }

    static ReceiveEndTurn * implRead(char *&) { return new ReceiveEndTurn(); }
};
#endif // GFSERVERMESS
