#ifndef NIM_MESSAGES_H
#define NIM_MESSAGES_H
#include "../server/format.h"
#include "../server/formatutils.h"
#include "../server/message.h"
#include <string>

/**
 * @brief A message that lets the clients know how many items were removed.
 */
class PlayerRemovedItems : public Message<PlayerRemovedItems> {
public:
    PlayerRemovedItems(int number) : number(number) { }

    int size() const { return Formats::size(&number); }
    void write(char *& dest) const { Formats::write(dest, &number); }

    const int number;

    static PlayerRemovedItems * implRead(char *&source) { return new PlayerRemovedItems(Formats::read<int>(source)); }
};



#endif // NIM_MESSAGES_H
