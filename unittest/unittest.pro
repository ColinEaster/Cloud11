TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    testgofish.cpp \
    testplayer.cpp \
    testdeck.cpp \
    testcard.cpp \
    testtable.cpp



INCLUDEPATH += gtest                       \
                 gtest/src                   \
                 gtest/src/gtest             \
                 gtest/include               \
                 gtest/include/gtest         \
                 gtest/include/gtest/internal

LIBS +=  -L/usr/lib -Wall -Wextra -pthread

SOURCES += "gtest/src/gtest.cc"            \
             "gtest/src/gtest-death-test.cc" \
             "gtest/src/gtest-filepath.cc"   \
             "gtest/src/gtest-port.cc"       \
             "gtest/src/gtest-printers.cc"   \
             "gtest/src/gtest-test-part.cc"  \
             "gtest/src/gtest-typed-test.cc"



HEADERS += ../GoFish/card.h \
    ../game/gameobject.h \
    ../game/gameobjectcontainer.h \
    ../game/abstractplayer.h \
    ../GoFish/deck.h \
    ../GoFish/player.h \
    ../GoFish/gofish.h \
    ../GoFish/table.h \
    testgofish.h \
    testplayer.h \
    testdeck.h \
    testcard.h \
    testtable.h

SOURCES += ../GoFish/card.cpp \
    ../game/gameobject.cpp \
    ../game/gameobjectcontainer.cpp \
    ../game/abstractplayer.cpp \
    ../GoFish/deck.cpp \
    ../GoFish/gofish.cpp \
    ../GoFish/table.cpp \
    ../GoFish/player.cpp

QMAKE_CXXFLAGS += -std=c++11
