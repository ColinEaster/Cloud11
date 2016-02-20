#ifndef GOFISH_GUI_H
#define GOFISH_GUI_H

#include <QWidget>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class goFish_GUI;
}

class goFish_GUI : public QWidget
{
    Q_OBJECT

public:
    explicit goFish_GUI(QWidget *parent = 0);
    ~goFish_GUI();
    void refresh_screen(vector<string> *table, vector<string> *hand, vector<string> *gamelog, string current_player, bool your_turn); /**< Method to refresh the screen. Calls clear_cards and spawn_cards */

private slots:
    int on_input_card_asked_returnPressed();

    void on_card1_clicked(); /**< magic tester button */

private:
    Ui::goFish_GUI *ui;
    vector<string> *table, *hand; /**< The table and hand, only for display in GUI */
    string cardSrc = ":/images/Playing_Cards_by_Byron_Knoll/"; /**< image resource filepath */
    bool input_visible; /**< Set input bar visible if true, i.e. if it is your turn. */

    void clear_cards(); /**< clear all cards on table and hand */
    void spawn_cards(vector<string> *table, vector<string> *hand); /**< add cards as given from server game */
    void append_gamelog(vector<string> *newgamelog); /**< append gamelog */
    void announce_current_player(string current_player, bool your_turn);

};

#endif // GOFISH_GUI_H
