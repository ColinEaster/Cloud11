TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++

#Internal

SOURCES += \
    card.cpp \
    deck.cpp \
    player.cpp \
    gofish.cpp \
    table.cpp \
    gofish_main.cpp

HEADERS += \
    card.h \
    deck.h \
    player.h \
    gofish.h \
    table.h

#External

SOURCES += \
    ../game/gameobject.cpp \
    ../game/gameobjectcontainer.cpp \
    ../game/game.cpp \
    ../game/abstractplayer.cpp \
    ../server/clientsocket.cpp \
    ../server/format.cpp

HEADERS += \
    ../game/gameobject.h \
    ../game/gameobjectcontainer.h \
    ../game/game.h \
    ../game/game.h \
    ../game/abstractplayer.h \
    ../server/clientsocket.h \
    ../server/format.h



