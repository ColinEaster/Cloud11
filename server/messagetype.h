#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

#include <iostream>

#include "messages.h"
#include "../GameServer/gamestart.h"
#include "../GameServer/gameover.h"
#include "../client_GUI/clientgui_message.h"
#include "../Nim/nim_messages.h"
//#include "../GoFishClient/gfclientmess.h"
#include "../GoFishServer/gfservermess.h"

enum class MessageType : int {
    DUMMY_Ping,

    C2S_JoinLobby,

    S2C_JoinLobbySuccess,
    S2C_JoinLobbyFailure,

    S2C_GameStart,
    C2S_GameStartSuccess,
    C2S_GameStartFailure,

    S2C_GameOver,
    C2S_GameOverSuccess,
    C2S_GameOverFailure,

    C2S_UpdateLobby,
    C2S_ChatInput,
    S2C_ChatIncoming,
    C2S_NimInput,
    S2C_NimIncoming,

    C2S2C_PlayerRemovedItems,
    S2C_PlayerTurn,
    C2S_ReceiveEndTurn,
    C2S_Ask,
    C2S_PutDown,

    ENUM_COUNT
};


template<MessageType E> struct EnumToMessage { };
template<typename T> struct MessageToEnum { };

template<int N> struct MessageMapping { };
template<MessageType E, typename T> struct MappingData {
    static constexpr MessageType Enum = E;
    using Type = T;
};

#define DEFINE_MAPPING(E, T) \
    template<> struct EnumToMessage<E> { using Type = T; }; \
    template<> struct MessageToEnum<T> { static constexpr MessageType Enum = E; }; \
    template<> struct MessageMapping<static_cast<int>(E)> { typedef MappingData<E, T> Result; };

constexpr int ENUM_FIRST = 0;
constexpr int ENUM_LAST = static_cast<int>(MessageType::ENUM_COUNT) - 1;

DEFINE_MAPPING(MessageType::DUMMY_Ping, Ping)

DEFINE_MAPPING(MessageType::C2S_JoinLobby, JoinLobby)
DEFINE_MAPPING(MessageType::S2C_JoinLobbySuccess, JoinLobbySuccess)
DEFINE_MAPPING(MessageType::S2C_JoinLobbyFailure, JoinLobbyFailure)

DEFINE_MAPPING(MessageType::S2C_GameStart, GameStart)
DEFINE_MAPPING(MessageType::C2S_GameStartSuccess, GameStartSuccess)
DEFINE_MAPPING(MessageType::C2S_GameStartFailure, GameStartFailure)

DEFINE_MAPPING(MessageType::S2C_GameOver, GameOver)
DEFINE_MAPPING(MessageType::C2S_GameOverSuccess, GameOverSuccess)
DEFINE_MAPPING(MessageType::C2S_GameOverFailure, GameOverFailure)
DEFINE_MAPPING(MessageType::C2S_UpdateLobby, UpdateLobby)
DEFINE_MAPPING(MessageType::C2S_ChatInput, ChatInput)
DEFINE_MAPPING(MessageType::S2C_ChatIncoming, ChatIncoming)
DEFINE_MAPPING(MessageType::C2S_NimInput, NimInput)
DEFINE_MAPPING(MessageType::S2C_NimIncoming, NimIncoming)

DEFINE_MAPPING(MessageType::S2C_PlayerTurn, PlayerTurn)
DEFINE_MAPPING(MessageType::C2S2C_PlayerRemovedItems, PlayerRemovedItems)

DEFINE_MAPPING(MessageType::C2S_ReceiveEndTurn, ReceiveEndTurn)
DEFINE_MAPPING(MessageType::C2S_Ask, Ask)
DEFINE_MAPPING(MessageType::C2S_PutDown, PutDown)

#endif // MESSAGETYPE_H
