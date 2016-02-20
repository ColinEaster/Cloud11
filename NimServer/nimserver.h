#ifndef NIMSERVER_H
#define NIMSERVER_H
#include "../GameServer/gameserver.h"
#include "../GameServer/gameover.h"
#include "../GameServer/gamestart.h"
#include <vector>
#include "../Nim/nim_messages.h"
#include "../game/abstractplayer.h"
#include "../game/gameobject.h"
#include "../game/gameobjectcontainer.h"
#include "../server/servermessagehandler.h"
#include "../server/clientid.h"
#include "../server/messagetype.h"


class NimServer:public GameServer
{
private:
    int items;
    std::vector<AbstractPlayer> player;
public:
    NimServer(int port);


    void handle(ClientID client, PlayerRemovedItems *message);

};

#endif // NIMSERVER_H
