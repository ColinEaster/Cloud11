QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG -= console
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++

#Internal

SOURCES += \
    gofishclient.cpp \
    gofishclient_main.cpp

HEADERS += \
    gfclientmess.h \
    gofishclient.h

#External

SOURCES += \
    ../game/gameobject.cpp \
    ../game/gameobjectcontainer.cpp \
    ../game/game.cpp \
    ../game/abstractplayer.cpp \
    ../GoFish/player.cpp \
    ../GoFish/card.cpp \
    ../GoFish/table.cpp \
    ../GoFish/deck.cpp \
    ../server/clientsocket.cpp \
    ../server/format.cpp

HEADERS += \
    ../game/gameobject.h \
    ../game/gameobjectcontainer.h \
    ../game/game.h \
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
    ../GoFish/deck.h \
    ../server/clientsocket.h \
    ../GoFishServer/gfservermess.h

