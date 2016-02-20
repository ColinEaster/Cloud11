#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

// TODO: File bug report, header falsely named, inclusion did not provide functionality.
#include <functional>
#include <iostream>

#include "messages.h"
#include "../GameServer/gamestart.h"
#include "../GameServer/gameover.h"
#include "../client_GUI/clientgui_message.h"
#include "../Nim/nim_messages.h"
//#include "../GoFishClient/gfclientmess.h"
#include "../GoFishServer/gfservermess.h"

#define MELT_STEEL_BEAMS(JETFUEL) \
    virtual void handle(JETFUEL *) { std::cout << "<MessageHandler>: Wake up, sheeple..." << std::endl; }

class MessageHandler {
public:
    virtual ~MessageHandler() { }

    MELT_STEEL_BEAMS(Ping)
    MELT_STEEL_BEAMS(JoinLobby)
    MELT_STEEL_BEAMS(JoinLobbySuccess)
    MELT_STEEL_BEAMS(JoinLobbyFailure)
    MELT_STEEL_BEAMS(GameStart)
    MELT_STEEL_BEAMS(GameStartSuccess)
    MELT_STEEL_BEAMS(GameStartFailure)
    MELT_STEEL_BEAMS(GameOver)
    MELT_STEEL_BEAMS(GameOverSuccess)
    MELT_STEEL_BEAMS(GameOverFailure)
    MELT_STEEL_BEAMS(UpdateLobby)
    MELT_STEEL_BEAMS(ChatInput)
    MELT_STEEL_BEAMS(ChatIncoming)
    MELT_STEEL_BEAMS(NimInput)
    MELT_STEEL_BEAMS(NimIncoming)
    MELT_STEEL_BEAMS(PlayerRemovedItems)
    MELT_STEEL_BEAMS(PlayerTurn)
    MELT_STEEL_BEAMS(ReceiveEndTurn)
    MELT_STEEL_BEAMS(Ask)
    MELT_STEEL_BEAMS(PutDown)


    template<typename cpp_templates_are_like_cacti>
    void handleTemplate(cpp_templates_are_like_cacti *message) {
        std::cout << "Socket received message type " << typeid(cpp_templates_are_like_cacti).name() << std::endl;
        this->handle(message);
    }
};

//template<typename Cthulhu>
//class SatisfyTheCompilationBloodlust {
//public:
//    SatisfyTheCompilationBloodlust(Cthulhu *TheAncientOne) : ElderGod(TheAncientOne) { }

//    template<typename ThereIsNoEscape>
//    void (*CallOfCthulhu(ThereIsNoEscape *))() {
//        return std::bind(&SatisfyTheCompilationBloodlust<Cthulhu>::HouseInRlyeh<ThereIsNoEscape>, ElderGod, std::placeholders::_1);
//    }

//    template<typename TerrorOfTheDeep>
//    static void HouseInRlyeh(Cthulhu *EvilIncarnate, TerrorOfTheDeep *DreamsOfTheDead) {
//        (EvilIncarnate->*&Cthulhu::handle)(DreamsOfTheDead);
//    }

//private:
//    Cthulhu *ElderGod;
//};

//class LesserDiety {
//    template<typename Zalgo>
//    void TwoMessagesOneHandle(Zalgo *HE_COMES);
//};

#endif // MESSAGEHANDLER_H
