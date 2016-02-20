TEMPLATE = subdirs

CONFIG -= console
CONFIG += c++11

SUBDIRS += \
    client_GUI \
    GoFish \
    game \
    unittest \
    server \
    Nim \
    GameServer \
    NimServer \
    GoFishServer \
    GoFishClient

QMAKE_CXXFLAGS += -stdlib=libc++
