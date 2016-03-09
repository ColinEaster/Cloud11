#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include <QWidget>
#include <vector>
#include <string>
#include "nim_gui.h"
#include "../server/messages.h"
#include "../server/clientsocket.h"
#include "../server/messagehandler.h"
#include "clientgui_message.h"
#include "../GameServer/gameserver.h"
#include "../game/game.h"
#include "../NimServer/nimserver.h"
#include "chat.h"
#include "../GameServer/gamestart.h"


using namespace std;

namespace Ui {
class client_GUI;
}

class client_GUI : public QWidget
{
    Q_OBJECT

public:
    static const int port_num = 31460;
    explicit client_GUI(QWidget *parent = 0);
    ~client_GUI();

    // old
//    void handle(JoinLobbySuccess *message);
//    void handle(ChatIncoming *msg);
//    void handle(NimIncoming *msg);
//    void handle(GameStart *);

    void thisPageIsOnFire();

//    void handle(HostLobby *msg);

    /*template<typename T>
    static void LaunchICBMs() {
        T *server = new T(port_num);
        static std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        std::condition_variable cv;
        while (true) cv.wait(lock);
    }*/

public slots:
    void receiveUpdatedPlayerList(std::vector<std::string> playerList);

signals:
    void nameEntered(std::string name);
    void ipAddressEntered(std::string ip);
    void hostDecision(bool willHost);
    void gameChosenInGui(std::string gameName);
    void startGamePressed(void);
    void clientGuiClosed();

private slots:
    /// reset default styles no accessible via stylesheet
    void reset_styles();

    /// UI page_0
    void on_IDInput_returnPressed();

    void on_IDConfirm_clicked();

    /// UI page_1
    void on_backto_page_0_clicked();

    void on_hostButton_clicked();

    void on_backto_page_1_f2_clicked();

    void on_creategameButton_clicked();

    void on_backto_page_1_f3_clicked();

    void on_kickButton_clicked();

    void on_joinButton_clicked();

    void on_backto_page_1_f4_clicked();

    void on_input_hostaddr_returnPressed();

    void on_searchjoinButton_clicked();

    void on_backto_page_1_f5_clicked();

    void on_promptButton_clicked();

    void on_startgameButton_clicked();

    void start_GoFish();

    void start_Nim();

    void showSelf();

    void on_input_IP_returnPressed();

private:
    Ui::client_GUI *ui;
    QString userID; /**< the userID for client */
    vector<string*> *playerList; /**< the list of players in the lobby you host. */
    string gameChosenFromList;
    Socket *CS;

    // old
//    GameServer *server;
//    Game *game;
//    chat *chatwindow;
//    Nim_GUI *nimwindow;
    void closeEvent(QCloseEvent *);

    template<typename T>
    static GameServer * makeServer(int port) {
        return static_cast<GameServer *>(new T(port));
    }
    template<typename T>
    static Game * makeGame(Socket *sock) {
        return static_cast<Game *>(new T(sock));
    }

    typedef GameServer*(*Silliness)(int);
    typedef Game*(*ClientSilliness)(Socket *);

    static std::map<std::string, Silliness> serverFunctions;
    static std::map<std::string, ClientSilliness> clientFunctions;


};

Q_DECLARE_METATYPE(string)
Q_DECLARE_METATYPE(vector<string>*)

#endif // CLIENT_GUI_H
