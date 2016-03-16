QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nim
TEMPLATE = app
CONFIG -= console
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++

SOURCES += \
    nim_main.cpp \
    nim.cpp

HEADERS += \
    nim.h \
    nim_messages.h

HEADERS += ../game/game.h
HEADERS += ../game/gameobject.h
HEADERS += ../game/gameobjectcontainer.h
HEADERS += ../game/abstractplayer.h

SOURCES += ../game/game.cpp
SOURCES += ../game/gameobject.cpp
SOURCES += ../game/gameobjectcontainer.cpp
SOURCES += ../game/abstractplayer.cpp\
    ../GameServer/gameserver.cpp\
    ../server/serversocket.cpp\

HEADERS += \
    ../server/messages.h \
    ../server/message.h \
    ../server/messageformat.h \
    ../server/messagehandler.h \
    ../server/messagetype.h \
    ../server/format.h \
    ../server/clientsocket.h \
    ../server/formatutils.h \
    ../client_GUI/client_gui.h \
    ../client_GUI/gofish_gui.h \
    ../client_GUI/nim_gui.h \
    ../client_GUI/chat.h \
    ../GameServer/gameserver.h\
    ../server/serversocket.h \
    ../NimServer/nimserver.h


RESOURCES += ../client_GUI/images.qrc
SOURCES += ../server/clientsocket.cpp
SOURCES += ../server/format.cpp
SOURCES += ../client_GUI/client_gui.cpp \
    ../client_GUI/gofish_gui.cpp \
    ../client_GUI/nim_gui.cpp \
    ../client_GUI/chat.cpp \
    ../NimServer/nimserver.cpp
FORMS    += ../client_GUI/client_gui.ui \
    ../client_GUI/gofish_gui.ui \
    ../client_GUI/nim_gui.ui \
    ../client_GUI/chat.ui

RESOURCES += ../client_GUI/images.qrc

