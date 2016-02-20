/* Copyright 2015 Colin Easter, Daniel Turchiano, Wah Loon Keng, Aaron Willey, and Nicholas Turney.

    This file is part of Cloud11.

    Cloud11 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Cloud11 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Cloud11.  If not, see <http://www.gnu.org/licenses/>.

    */
#include "gofish_gui.h"
#include "ui_gofish_gui.h"

/**
 * @brief goFish_GUI::goFish_GUI
 * @param parent
 * Constructor. Initializes table and hand. pulls up UI.
 */
goFish_GUI::goFish_GUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::goFish_GUI)
{
    ui->setupUi(this);
///    Initialize table and hand
    table = new vector<string>();
    hand = new vector<string>();
    /// first hide input bar since it's not your turn yet
    input_visible = false;
    ui->input_card_asked->setVisible(input_visible);
    ui->stackedWidget->setCurrentIndex(0); /**< Init to page 0 */
    ui->game_log->clear();
//    this->showFullScreen();
}
/**
 * @brief goFish_GUI::~goFish_GUI
 * Destructor.
 */
goFish_GUI::~goFish_GUI()
{
    delete ui;
}

/**
 * Method called to refresh the goFish GUI screen for this player.
 * set input field visible if it's this player's turn to play.
 * @brief goFish_GUI::refresh_screen
 * @param newtable The new table updated from server game
 * @param newhand   The new hand of this player, updated from server game
 * @param newgamelog The gamelog: player moves in the past turn.
 * @param current_player The userID of the current player (may not be unique)
 * @param your_turn Whether or not it's this player's turn.
 */
void goFish_GUI::refresh_screen(vector<string> *newtable, vector<string> *newhand, vector<string> *newgamelog, string current_player, bool your_turn)
{
    clear_cards(); /**< clear cards from table and hand */
    spawn_cards(newtable, newhand); /**< add cards to table and hand as updated */
    append_gamelog(newgamelog); /**< prepend new gamelog to top */
    announce_current_player(current_player, your_turn); /**< update message which shows who's the current player */
}

/**
 * @brief goFish_GUI::clear_cards
 * Clear all cards from table and hand.
 */
void goFish_GUI::clear_cards()
{
    QLayoutItem *card;
    while ( (card = ui->table_row_1->takeAt(0)) != 0 )
        delete card->widget();
    while ( (card = ui->table_row_2->takeAt(0)) != 0 )
        delete card->widget();
    while ( (card = ui->hand->takeAt(0)) != 0 )
        delete card->widget();
}
/**
 * @brief goFish_GUI::spawn_cards
 * @param newtable
 * @param newhand
 * Called after clear_cards(): Add cards to table and hand as updated from server.
 */
void goFish_GUI::spawn_cards(vector<string> *newtable, vector<string> *newhand)
{
    /// update the table and hand vector variables.
    table = newtable; hand = newhand;
    QPushButton *newcard;
    /// update table
    for (size_t i = 0; i < table->size(); ++i)
    {
        /// create new card from updated table, set fixed size
        newcard = new QPushButton(QIcon(QString::fromStdString(cardSrc + (*table)[i])), "", 0);
        newcard->setFixedSize(QSize(80, 116));
        newcard->setIconSize(QSize(80, 116));
        /// alternatively add to table row1 and row2
        if (i%2 == 0)
            ui->table_row_1->addWidget(newcard, 0, 0);
        else
            ui->table_row_2->addWidget(newcard, 0, 0);
    }
    /// update hand
    for (auto it = hand->begin(); it!= hand->end(); ++it)
    {
        /// create new card from updated hand, set fixed size
        newcard = new QPushButton(QIcon(QString::fromStdString(cardSrc + *it)), "", 0);
        newcard->setFixedSize(QSize(80, 116));
        newcard->setIconSize(QSize(80, 116));
        ui->hand->addWidget(newcard, 0, 0);
    }
    /// garbage collection
    delete table;
    delete hand;
}

/**
 * @brief goFish_GUI::append_gamelog
 * @param newgamelog
 * Append game log as updated per turn.
 */
void goFish_GUI::append_gamelog(vector<string> *newgamelog)
{
    QListWidgetItem *item;
    for (auto it = newgamelog->begin(); it!= newgamelog->end(); ++it)
    {
        item = new QListWidgetItem(QString::fromStdString(*it));
        ui->game_log->insertItem(0, item); /**< add a log */
        ui->game_log->setCurrentItem(item); /**< select and highlight it to focus */
    }
}
/**
 * @brief goFish_GUI::announce_current_player
 * @param current_player the userID of the current player.
 * @param your_turn true if it's this player's turn
 * Server tells you who's turn is it to play now by setting the message.
 * Set input field visible if it's this player's turn.
 */
void goFish_GUI::announce_current_player(string current_player, bool your_turn)
{
    /// update input_visible: if it's your turn, unhide the input bar
    input_visible = your_turn;
    ui->input_card_asked->setVisible(input_visible);
    /// update message announcing who's turn is it now
    if (your_turn)
        ui->title_player_turn->setText(QString::fromStdString("Your Turn"));
    else
        ui->title_player_turn->setText(QString::fromStdString(current_player+"'s Turn"));
}

/**
 * @brief goFish_GUI::on_input_card_asked_returnPressed
 * User Input: Take user input and deactivate (hide) input field (if input not empty).
 */
int goFish_GUI::on_input_card_asked_returnPressed()
{
    QString tmp = ui->input_card_asked->text(); /**< set the userID for client */
    if (tmp.length()>0) /**< check nonempty */
    {
        input_visible = false;
        ui->input_card_asked->setVisible(input_visible); /**< hide input box */
        return tmp.toInt(); /**< convert input to int, return */
    }
    else {}
    //else do nothing
}


/// Magic tester method: click first card in hand to activate
void goFish_GUI::on_card1_clicked()
{
    // Testing refresh
    vector<string> *v1 = new vector<string>();
    v1->push_back("2_of_clubs.jpg");
    v1->push_back("3_of_clubs.jpg");
    v1->push_back("4_of_clubs.jpg");
    v1->push_back("5_of_clubs.jpg");
    v1->push_back("6_of_clubs.jpg");
    v1->push_back("7_of_clubs.jpg");
    v1->push_back("8_of_clubs.jpg");
    vector<string> *v2 = new vector<string>();
    v2->push_back("2_of_diamonds.jpg");
    v2->push_back("3_of_diamonds.jpg");
    v2->push_back("4_of_diamonds.jpg");
    v2->push_back("5_of_diamonds.jpg");
    v2->push_back("6_of_diamonds.jpg");
    v2->push_back("7_of_diamonds.jpg");
    v2->push_back("8_of_diamonds.jpg");
    vector<string> *v3 = new vector<string>();
    v3->push_back("Player 1 Go Fish!");
    string name = "Keng";
    bool your_turn = true;

//    Test: call the refresh screen method
    refresh_screen(v1,v2, v3, name, your_turn);

}
