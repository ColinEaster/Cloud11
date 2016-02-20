#ifndef GOFISHCLIENT_H
#define GOFISHCLIENT_H
#include "../GoFish/deck.h"
#include "../GoFish/table.h"
#include "gfclientmess.h"
#include "../GoFishServer/gfservermess.h"
#include "../game/game.h"
#include "../server/messagehandler.h"

class GoFishClient : public Game
{
public:
    GoFishClient(Player p, Socket* socket);

    void run();
    int menu();
    void turn();
    void ask();
    void putDown();

    /**
     * @brief handle(AllPlayers *message) This handler's goal is to receive a list of Players. It stores them
     * to this GoFishClient file in 'Them'. The important thing about this is that each of the Players' names and IDs
     * are stored in Them.
     *
     * Additionally turnCounter is set to message->ThesePlayers.size()
     */
    void handle(AllPlayers *message);
    /**
     * @brief handle(AllPlayers *message) This handler's goal is to find the starting player using the clientID.
     * if the owner of the clientID is 'Me' then turnCounter is set to 0. Otherwise, the StartingPlayer is found accordingly.
     * Once found the methods ends, however, if no candidates for startingPlayer are found, then the method sets turnCounter to
     * Them.size()+1 and prints an error message.
     */
    void handle(StartingPlayer *message);
    /**
     * @brief handle(ReceiveHand* message) This handler takes a vector of Cards and appends it to 'Me's hand. This method
     * should usually only be called at the beginning of the game, when everybody is dealt cards.
     */
    void handle(ReceiveHand* message);
    /**
     * @brief handle(ReceiveCards* message) This handler performs the same action as StartingPlayer's with an exception.
     * This message will print a contextual message explaining how many of the kind of Card received were given to you, by the Player
     * to your left. All Cards involved in this message should have the same rank, so it only requires the rank of one card in
     * the set to know what Cards are being used.
     */
    void handle(ReceiveCards* message);
    /**
     * @brief handle(TurnEnd* message) This handler is just an indicator that a Player's turn has ended.
     *
     * It increments turnCounter by one.
     */
    void handle(TurnEnd* message);
    /**
     * @brief handle(AskEventPersonal *message) This handler handles the situation where a Player to your right has asked you for a
     * card of rank message->askRank(). If you have cards available then the method prints context as to how many Cards you gave them.
     * Otherwise you tell the Player to Go Fish.
     */
    void handle(AskEventPersonal *message);
    /**
     * @brief handle(AskEvent *message) This handler handles the situation where some Player has asked another Player for a
     * card of rank message->askRank(). This method only prints what one Player asked another for.
     */
    void handle(AskEvent *message);
    /**
     * @brief handle(AskEvent_Size *message) This handler is a followup to the AskEvent handler if the Player who has been asked
     * has cards to give to the Asker. This method prints how many cards one Player has transferred to another.
     */
    void handle(AskEvent_Size* message);
    /**
     * @brief handle(AskEvent_Fish *message) This handler is a followup to the AskEvent handler if the Player who has been asked does
     * not have any cards to give to the Asker. This method just prints one player telling another Go Fish.
     */
    void handle(AskEvent_Fish* message);
    /**
     * @brief handle(ReceiveWinString *message) This handler just prints the victory string with the Player's names generated in
     * GoFishClient Server. This method also turns winCheck true.
     */
    void handle(ReceiveWinString* message);
    void handle(UpdateHand* message);
    void handle(UpdateScore* message);
    void handle(ReceiveFish* message);

private:
    bool winCheck;
    /**
     * @brief Me The Player and his information.
     */
    Player Me;
    /**
     * @brief Them The opposing Players and their names and IDs. At most this vector should only have that information.
     */
    std::vector<Player> Them;
    /**
     * @brief turnCounter Keeps track of who's turn it is. This value is set upon handling a StartingPlayer message
     *
     * 0 - Me
     * 1 - Them[0]
     * 2 - Them[1]
     * ...
     * n-1 - Them[n-2]
     * n - Them[n-1]
     */
    int turnCounter;
};

#endif // GOFISHCLIENT_H
