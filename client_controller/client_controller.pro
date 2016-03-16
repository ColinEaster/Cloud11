QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client_controller
TEMPLATE = app
CONFIG -= console
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++

SOURCES += main.cpp \
    client_controller.cpp \
    ../client_GUI/client_gui.cpp

HEADERS += \
    client_controller.h \
    ../client_GUI/client_gui.h


#FORMS    += ../client_GUI/client_gui.ui \
 #   ../client_GUI/gofish_gui.ui \
  #  ../client_GUI/nim_gui.ui \
   # ../client_GUI/chat.ui

SOURCES +=  ../server/clientsocket.cpp\
    ../server/serversocket.cpp\
    ../server/format.cpp\
    ../GameServer/gameserver.cpp\
    ../NimServer/nimserver.cpp \
    ../Nim/nim.cpp \
    ../game/game.cpp \
    ../game/gameobject.cpp \
    ../game/gameobjectcontainer.cpp \
    ../client_GUI/chat.cpp \
    ../client_GUI/gofish_gui.cpp \
    ../client_GUI/nim_gui.cpp

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
    ../GoFishClient/gfclientmess.h \
    ../client_GUI/chat.h \
    ../client_GUI/gofish_gui.h \
    ../client_GUI/nim_gui.h

RESOURCES += ../client_GUI/images.qrc
