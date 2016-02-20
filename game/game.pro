TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    gameobject.cpp \
    gameobjectcontainer.cpp \
    game.cpp \
    abstractplayer.cpp \
    game_main.cpp \
    ../server/clientsocket.cpp \
    ../server/format.cpp

HEADERS += \
    gameobject.h \
    gameobjectcontainer.h \
    game.h \
    game.h \
    abstractplayer.h \
    ../server/clientsocket.h \
    ../server/messagehandler.h \
    ../server/format.h

HEADERS += ../GameServer/gamestart.h \
    ../GameServer/gameover.h \
    ../GoFishServer/gfservermess.h \
    ../GoFishClient/gfclientmess.h


QMAKE_CXXFLAGS += -std=c++11
