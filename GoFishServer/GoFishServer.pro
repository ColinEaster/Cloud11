TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++

#Internal

SOURCES += \
    gofishserver.cpp \
    gofishserver_main.cpp

HEADERS += \
    gfservermess.h \
    gofishserver.h

#External

SOURCES += \
    ../GameServer/gameserver.cpp \
    ../game/gameobject.cpp \
    ../game/gameobjectcontainer.cpp \
    ../game/game.cpp \
    ../game/abstractplayer.cpp \
    ../GoFish/player.cpp \
    ../GoFish/card.cpp \
    ../GoFish/table.cpp \
    ../GoFish/deck.cpp \
    ../server/format.cpp \
    ../server/clientsocket.cpp \
    ../server/serversocket.cpp

HEADERS += \
    ../GoFishClient/gfclientmess. \
    ../GameServer/gameover.h \
    ../GameServer/playermessage.h \
    ../GameServer/gameserver.h \
    ../GameServer/gamestart.h \
    ../game/gameobject.h \
    ../game/game.h \
    ../game/abstractplayer.h \
    ../server/messages.h \
    ../server/message.h \
    ../server/messageformat.h \
    ../server/messagehandler.h \
    ../server/messagetype.h \
    ../server/format.h \
    ../server/clientsocket.h \
    ../server/formatutils.h \
    ../GoFish/player.h \
    ../GoFish/card.h \
    ../GoFish/table.h \
    ../GoFish/deck.h


