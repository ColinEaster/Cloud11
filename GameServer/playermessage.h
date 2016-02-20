#ifndef PLAYERMESSAGE_H
#define PLAYERMESSAGE_H

#endif // PLAYERMESSAGE_H

/**
 * @brief From the getTurn() in gameserver class The PlayerMessage takes a 0 to (total players - 1) representing either the host or other players turn
 */

class PlayerMessage : public Message<PlayerMessage> {
public:
    PlayerMessage(int id) : id(id) { }

    int size() const { return Formats::size(&start); }
    void write(char *& dest) const { Formats::write(dest, &start); }

    const int id;

    static PlayerMessaage * implRead(char *&source) { return new PlayerMessage(Formats::read<int>(source)); }
};
