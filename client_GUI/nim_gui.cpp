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
#include "nim_gui.h"
#include "ui_nim_gui.h"
#include <QMessageBox>

/**
 * @brief Nim_GUI::Nim_GUI
 * @param parent
 * Constructor. Initializes table.
 */
Nim_GUI::Nim_GUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nim_GUI)
{
    ui->setupUi(this);
    /// first hide input bar since it's not your turn yet
    input_visible = false;
    ui->input_asked->setVisible(input_visible);
    ui->stackedWidget->setCurrentIndex(0); /**< Init to page 0 */
    /// Quick style resets
    ui->input_asked->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->game_log->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->game_log->clear();

    /**< 1 player emergency backup */
    /**< 1 player emergency backup */
   // spawn_stones(100);
    on_stone_9_clicked();
    /**< 1 player emergency backup */
    /**< 1 player emergency backup */
}
/**
 * @brief Nim_GUI::~Nim_GUI
 * Destructor
 */
Nim_GUI::~Nim_GUI()
{
    delete ui;
}
/**
 * @brief chat::setClientSocket
 * @param parentCS
 * Pass the parent Socket from client GUI for it to use.
 */
void Nim_GUI::setClientSocket(Socket *parentCS)
{
    CS = parentCS;
}
/**
 * Refresh the Nim GUI screen for this player.
 * set input field visible if it's this player's turn to play.
 * @brief Nim_GUI::refresh_screen
 * @param stones_remain The number of remaining stones
 * @param newgamelog The gamelog: player moves in the past turn.
 * @param current_player The userID of the current player (may not be unique)
 * @param your_turn Whether or not it's this player's turn.
 */
void Nim_GUI::refresh_screen(int stone_taken, int stones_remain, vector<string> *newgamelog, string current_player, bool your_turn)
{
    //cout << "GUI receiving thread: " << std::this_thread::get_id() << endl;
    oneplayerstonenum = stones_remain;
    ui->title_stones_remain->setText(QString::number(stones_remain) + QString::fromStdString(" stones remain."));
    clear_stones(stones_remain); /**< clear stones from table */
    spawn_stones(stones_remain); /**< add stones to table as told by server */
    append_gamelog(newgamelog); /**< prepend new gamelog */
    announce_current_player(current_player, your_turn); /**< update message to announce player's turn */
    cout << "inside refresh, done" << endl;
    if (oneplayerstonenum < 2) {
        QMessageBox msgBox;
        msgBox.setText("End of game.");
        msgBox.setInformativeText("We hope you enjoy!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int res = msgBox.exec();
        if (res == QMessageBox::Ok) {
            this->hide();
//            papa->thisPageIsOnFire();
            this->destroy(true, true);
        }
    }
}

/**
 * @brief Nim_GUI::clear_stones
 * Clear all stones from table (5 rows).
 */
void Nim_GUI::clear_stones(int stones_remain)
{
    QLayoutItem *stone;
    while ( (stone = ui->stone_row_1->takeAt(0)) != 0 )
        stone->widget()->hide();
    while ( (stone = ui->stone_row_2->takeAt(0)) != 0 )
        stone->widget()->hide();
    while ( (stone = ui->stone_row_3->takeAt(0)) != 0 )
        stone->widget()->hide();
    while ( (stone = ui->stone_row_4->takeAt(0)) != 0 )
        stone->widget()->hide();
    while ( (stone = ui->stone_row_5->takeAt(0)) != 0 )
        stone->widget()->hide();

//    for (int i = 0; i < stones_remain; ++i)
//    {
//        int j = i%5;
//        switch(j)
//        {
//        case 0: while ( (stone = ui->stone_row_1->takeAt(0)) != 0 ) {
//            if(!stone->widget()->isHidden()){
//                stone->widget()->hide();
//                break;
//            }
//        } break;
//        case 1: while ( (stone = ui->stone_row_2->takeAt(0)) != 0 ) {
//            if(!stone->widget()->isHidden()){
//                stone->widget()->hide();
//                break;
//            }
//        } break;
//        case 2: while ( (stone = ui->stone_row_3->takeAt(0)) != 0 ) {
//            if(!stone->widget()->isHidden()){
//                stone->widget()->hide();
//                break;
//            }
//        } break;
//        case 3: while ( (stone = ui->stone_row_4->takeAt(0)) != 0 ) {
//            if(!stone->widget()->isHidden()){
//                stone->widget()->hide();
//                break;
//            }
//        } break;
//        case 4: while ( (stone = ui->stone_row_5->takeAt(0)) != 0 ) {
//            if(!stone->widget()->isHidden()){
//                stone->widget()->hide();
//                break;
//            }
//        } break;
//        default: break;
//        }
//    }
}

/**
 * @brief Nim_GUI::spawn_stones
 * @param stones_remain
 * Called after clear_stones(): Add stones to table as server tells.
 */
void Nim_GUI::spawn_stones(int stones_remain)
{
    QPushButton *newstone;
    for (int i = 0; i < stones_remain; ++i)
    {
        /// create a new stone (pushButton)
        newstone = new QPushButton(QIcon(QString::fromStdString(stoneSrc)), "", 0);
        newstone->setFixedSize(QSize(30,30));
        newstone->setIconSize(QSize(30,30));
        newstone->setStyleSheet("border:none;");
        /// Add to next row
        int j = i%5;
        switch(j)
        {
            case 0: ui->stone_row_1->addWidget(newstone, 0, 0); break;
            case 1: ui->stone_row_2->addWidget(newstone, 0, 0); break;
            case 2: ui->stone_row_3->addWidget(newstone, 0, 0); break;
            case 3: ui->stone_row_4->addWidget(newstone, 0, 0); break;
            case 4: ui->stone_row_5->addWidget(newstone, 0, 0); break;
        default: break;
        }
    }
    /// Update message to display number of stones now.
    ui->title_stones_remain->setText(QString::number(stones_remain) + QString::fromStdString(" stones remain."));
}

/**
 * @brief Nim_GUI::append_gamelog
 * @param newgamelog
 * Update the gamelog per turn.
 */
void Nim_GUI::append_gamelog(vector<string> *newgamelog)
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
 * @brief Nim_GUI::announce_current_player
 * @param current_player
 * @param your_turn
 * Server tells you who's turn is it to play now by setting the message.
 * Set input field visible if it's this player's turn.
 */
void Nim_GUI::announce_current_player(string current_player, bool your_turn)
{
    /// update input_visible: if it's your turn, unhide the input bar
    input_visible = your_turn;
    ui->input_asked->setVisible(input_visible);
    /// update message announcing who's turn is it now
    if (your_turn)
        ui->title_player_turn->setText(QString::fromStdString("Your Turn"));
    else
        ui->title_player_turn->setText(QString::fromStdString(current_player+"'s Turn"));
}
/**
 * @brief Nim_GUI::on_input_asked_returnPressed
 * User Input: Take user input and deactivate (hide) input field (if input not empty).
 */
int Nim_GUI::on_input_asked_returnPressed()
{
    QString tmp = ui->input_asked->text();
    if (tmp.length()>0) /**< check nonempty */
    {
        oneplayerstonenum -= tmp.toInt();
        NimInput *nimmsg = new NimInput(tmp.toInt(), oneplayerstonenum, tmp.toStdString() + " stones taken.", 1);
        CS->send(nimmsg);
//        delete nimmsg;
        moved = true;
        input_visible = false;
        ui->input_asked->setVisible(input_visible); /**< hide input box */

        /**< 1 player emergency backup */
        /**< 1 player emergency backup */
        /**< 1 player emergency backup */
//        oneplayerstonenum -= tmp.toInt();
        vector<string> *firelog = new vector<string>();
        firelog->push_back("You took " + tmp.toStdString());
        string me = "You";
        bool your_turn = true;
//        refresh_screen(oneplayerstonenum, firelog, me, your_turn);
        /**< 1 player emergency backup */
        /**< 1 player emergency backup */
        /**< 1 player emergency backup */
        ui->input_asked->clear();
        return tmp.toInt(); /**< convert input to int, return */
    }
    else {}
    //else do nothing
    ui->input_asked->clear();
}

int Nim_GUI::get_input() {
    if (moved) {
        moved = false;
        return input;
    }
    else {
        return -1;
    }
}

/// Magic tester method: click the bottom left stone to activate
void Nim_GUI::on_stone_9_clicked()
{
    vector<string> *v3 = new vector<string>();
    v3->push_back("The game begins!");
    string name = "Keng";
    bool your_turn = true;
//    ui->game_log->clear();

    //    Test: call the refresh screen method
    refresh_screen(0, 100, v3, name, your_turn);
}


/**
 * @brief Nim_GUI::setPapa
 * @param dada
 * Set parent client_GUI to reshow it.
 */
//void Nim_GUI::setPapa(client_GUI *dada)
//{
//    papa = dada;
//}
