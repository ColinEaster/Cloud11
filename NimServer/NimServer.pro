TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    nimserver.cpp

HEADERS += \
    ../GameServer/gameserver.h \
    ../GameServer/gamestart.h \
    ../server/messages.h\
    ../server/message.h \
    ../server/messageformat.h \
    ../server/messagehandler.h \
    ../server/messagetype.h \
    ../server/format.h \
    ../server/clientsocket.h \
    ../server/formatutils.h \
    ../server/serversocket.h \
    ../server/clientid.h \
    ../server/servermessagehandler.h \
    ../GameServer/gameover.h \
    ../GameServer/gamestart.h \
    ../GameServer/playermessage.h \
    ../Nim/nim_messages.h \
    ../game/abstractplayer.h \
    ../game/gameobject.h \
    ../game/gameobjectcontainer.h \
    nimserver.h

SOURCES+= ../server/format.cpp \
    ../server/clientsocket.cpp \
    ../game/abstractplayer.cpp \
    ../game/gameobject.cpp \
    ../game/gameobjectcontainer.cpp \
    ../GameServer/gameserver.cpp \
    ../server/serversocket.cpp

LIBS += -pthread

QMAKE_CXXFLAGS += -pthread -std=c++11


