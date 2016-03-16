#ifndef NIM_GUI_H
#define NIM_GUI_H

#include <QWidget>
#include <vector>
#include <string>

#include "clientgui_message.h"
#include "../server/messages.h"
#include "../server/clientsocket.h"
#include "../server/messagehandler.h"

//#include "client_gui.h"


namespace Ui {
class Nim_GUI;
}

class Nim_GUI : public QWidget
{
    Q_OBJECT

public:
    explicit Nim_GUI(QWidget *parent = 0);
    ~Nim_GUI();
    void setClientSocket(Socket *parentCS);

    int get_input();
    bool moved = false;
//    void setPapa(client_GUI *dada);

public slots:
    void displayStones(int);
    void updatePlayerList(std::vector<std::string>);
    void displayMessage(std::string);
    void allowInput(bool);
    void announce_current_player(std::string current_player, bool your_turn);
    void refresh_screen(int stone_taken, int stones_remain, std::vector<std::string> gamelog, std::string current_player, bool your_turn); /**< Method to refresh the screen. */

signals:
    void playerWantsToRemoveStones(int);

private slots:
    void on_stone_9_clicked();

    int on_input_asked_returnPressed();

private:
    Ui::Nim_GUI *ui;
    Socket *CS; /**< socket from parent client GUI */
    std::string stoneSrc = ":images/circle.png"; /**< image resource filepath */
    bool input_visible; /**< Set input bar visible if true, i.e. if it is your turn. */

    void clear_stones(int stones_remain); /**< clear all stones on table and hand */
    void spawn_stones(int stones_remain); /**< add stones as given from server game */
    void append_gamelog(const std::vector<std::string> &newgamelog); /**< append gamelog */

    void clearInput(bool);

    int oneplayerstonenum = 20;

    int input = -1;
//    client_GUI *papa;
};

#endif // NIM_GUI_H
