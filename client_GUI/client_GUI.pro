#-------------------------------------------------
#
# Project created by QtCreator 2015-04-11T14:56:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client_GUI
TEMPLATE = app
CONFIG -= console
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++

SOURCES += client_main.cpp\
        client_gui.cpp \
    gofish_gui.cpp \
    nim_gui.cpp \
    chat.cpp

HEADERS  += client_gui.h \
    gofish_gui.h \
    nim_gui.h \
    clientgui_message.h \
    chat.h

FORMS    += client_gui.ui \
    gofish_gui.ui \
    nim_gui.ui \
    chat.ui

RESOURCES += images.qrc


SOURCES +=  ../server/clientsocket.cpp\
    ../server/serversocket.cpp\
    ../server/format.cpp\
    ../GameServer/gameserver.cpp\
    ../NimServer/nimserver.cpp \
    ../Nim/nim.cpp \
    ../game/game.cpp \
    ../game/gameobject.cpp \
    ../game/gameobjectcontainer.cpp

HEADERS += ../server/clientsocket.h\
    ../server/serversocket.h\
    ../server/messageformat.h\
    ../server/format.h\
    ../server/formatutils.h\
    ../server/message.h\
    ../server/messages.h\
    ../server/messagetype.h\
    ../server/messagehandler.h\
    ../GameServer/gameserver.h\
    ../NimServer/nimserver.h \
    ../Nim/nim.h \
    ../game/game.h \
    ../game/gameobject.h \
    ../game/gameobjectcontainer.h \
    ../GoFishServer/gfservermess.h \
    ../GoFishClient/gfclientmess.h

