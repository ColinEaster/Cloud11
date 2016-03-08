TEMPLATE = subdirs

CONFIG -= console
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++

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
    GoFishClient\
    client_controller


