TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    clientsocket.cpp \
    format.cpp \
    serversocket.cpp

HEADERS += \
    format.h \
    message.h \
    messagetype.h \
    clientsocket.h \
    messageformat.h \
    formatutils.h \
    messages.h \
    messagehandler.h \
    vectorformat.h \
    serversocket.h \
    servermessagehandler.h \
    clientid.h \
    ../GoFishServer/gfservermess.h \
    ../GoFishClient/gfclientmess.h \
    ../GameServer/gamestart.h  \
    ../GameServer/gameover.h \
    ../Nim/nim_messages.h

LIBS += -pthread
QMAKE_CXXFLAGS += -pthread -std=c++11
