TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++

SOURCES += main.cpp \
    gameserver.cpp

HEADERS += \
    gameserver.h \
    gamestart.h \
    ../server/messages.h\
    ../server/message.h \
    ../server/messageformat.h \
    ../server/servermessagehandler.h \
    ../server/messagetype.h \
    ../server/format.h \
    ../server/clientsocket.h \
    ../server/formatutils.h \
    ../server/cliendid.h \
    ../server/serversocket.h \
    gameover.h \
    playermessage.h \
    ../GoFishServer/gfservermess.h \
    ../GoFishClient/gfclientmess.h

SOURCES+= ../server/format.cpp \
    ../server/clientsocket.cpp \
    ../server/serversocket.cpp

LIBS += -pthread
QMAKE_CXXFLAGS += -pthread -std=c++11
