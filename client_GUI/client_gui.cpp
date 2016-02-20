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
#include "client_gui.h"
#include "ui_client_gui.h"
#include <QMessageBox>
#include "gofish_gui.h"
#include "nim_gui.h"
#include "../server/clientsocket.h"
#include "../server/serversocket.h"
#include "../GameServer/gameserver.h"
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "chat.h"
#include "../Nim/nim.h"

/**
 * @brief client_GUI::client_GUI
 * @param parent
 * client_GUI constructor, with initialization.
 */
client_GUI::client_GUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client_GUI)
{
    //cout << "GUI main thread: " << std::this_thread::get_id() << endl;
    ui->setupUi(this);
//    this->setAttribute( Qt::WA_DeleteOnClose );
    ui->stackedWidget->setCurrentIndex(0); /**< Init: go to UI page_0 */
    userID = "NACK"; /**< Init userID */
    playerList = new vector<string*>(); /**< Init playerList. To be added from server. */
    reset_styles(); /**< Reset styles */

}
/** Destructor */
client_GUI::~client_GUI()
{
    delete chatwindow;
    delete CS;
    delete ui;
}


void client_GUI::closeEvent(QCloseEvent *)
{
    delete chatwindow;
    delete CS;
//    chatwindow->hide();
//    delete this;
}

/** reset default styles no accessible via stylesheet */
void client_GUI::reset_styles()
{
    /// remove the outline when in focus
    ui->IDInput->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->game_list->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->player_list->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->input_hostaddr->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->player_list_joined->setAttribute(Qt::WA_MacShowFocusRect, 0);
//    this->window()->setAttribute( Qt::WA_DeleteOnClose );
}

/**
 * ------------------------------------------------
 * UI page_0: userID creation
 * ------------------------------------------------
 */

/**
 * @brief client_GUI::on_IDInput_returnPressed
 * the IDInput textbox on "enter"
 * ensure nonempty input; bypass button; go to UI page 1
 * save the ID of player on machine.
 */
void client_GUI::on_IDInput_returnPressed()
{
    userID = ui->IDInput->text(); /**< set the userID for client */
    if (userID.length()>0) /**< check nonempty */
    {
        ui->IDOutput->setText(userID); /**< set IDOutput of UI page_1 */
        ui->stackedWidget->setCurrentIndex(1); /**< go to page_1 */
    }
}
/**
 * @brief client_GUI::thisPageIsOnFire
 * 1 player emergency backup
 */
void client_GUI::thisPageIsOnFire()
{
    on_IDInput_returnPressed();
    this->show();
}

/**
 * @brief client_GUI::on_IDConfirm_clicked
 * Dummy button for IDInput; simulates "enter".
 */
void client_GUI::on_IDConfirm_clicked()
{
    on_IDInput_returnPressed();
}


/**
 * ------------------------------------------------
 * UI page_1: Host or Join
 * ------------------------------------------------
 */

/** Back to change ID: page_0 from page_1 */
void client_GUI::on_backto_page_0_clicked()
{
    /// clear ID input box and reset userID to default
    ui->IDInput->clear();
    userID = "NACK";
    ui->stackedWidget->setCurrentIndex(0);
}
/** To Hosting: page_2 */
void client_GUI::on_hostButton_clicked()
{
    ui->game_list->clearSelection(); /**< clear the selection on game_list */
    delete playerList;
    playerList = new vector<string*>(); /**< reset the playerList stored in class */
    ui->player_list->clear(); /**< clear the player_list in GUI */
    ui->stackedWidget->setCurrentIndex(2);
}
/** To Joining: page_4 */
void client_GUI::on_joinButton_clicked()
{
    ui->input_hostaddr->clear(); /**< clear the input field for hostaddr */
//    ui->join_status->clear(); /**< clear the status at bottom */
    ui->stackedWidget->setCurrentIndex(4);

}



/**
 * ------------------------------------------------
 * UI page_2: Hosting
 * ------------------------------------------------
 */

/** Back to Host/Join: Go to page_1 from page_2 */
void client_GUI::on_backto_page_1_f2_clicked()
{
    /// close server, make invisible
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief validChoice
 * Quickly check if a chosen game is valid
 * @param item
 * @return true if valid choice.
 */
bool validChoice(QListWidgetItem *item) {
    return (item->text() == "Go Fish" || item->text() == "Nim");
};

/**
 * @brief client_GUI::on_creategameButton_clicked
 * Chosen a game
 * To Lobby: page_3 Lobby from page_2
 */
void client_GUI::on_creategameButton_clicked()
{
    /// Initialize the player_list in page_3
    QList<QListWidgetItem*> game_selected = ui->game_list->selectedItems(); /**< the game chosen */
    /// The port number entered; parsed as QString first
    QString myIP = ui->input_IP->text();

    if (game_selected.length()>0 && myIP.length() > 0 && validChoice(game_selected[0]) ) /**< ensure game select before to page_3 */
    {
        QListWidgetItem *game_chosen = game_selected[0]; /**< Pass the name of game chosen */
        gameChosen = game_chosen->text().toStdString(); /**< set the game chosen of client */
        ui->title_gamechosen->setText(game_chosen->text()); /**< Set game name in page_3 */
        ui->kickButton->hide(); /**< temporarily hide the kick button */
        /// create server and make visible
        /// set game chosen, prepare to init gameUI
        /// retrieve hostaddr and display
        ui->host_address->setText("Google this: \"my IP\"");

        ui->player_list->insertItem(0, userID); /**< Populate player_list with host's userID */
        ui->stackedWidget->setCurrentIndex(3); /**< go to page_3 */

        /// Launch Server
        //std::thread(&(client_GUI::LaunchICBMs<GameServer>)).detach();
        server = serverFunctions[gameChosen](port_num);

        /**< 1 player emergency backup */
        /**< 1 player emergency backup */
        /// Connect the the server aforesaid
        CS = new Socket(myIP.toStdString().c_str(), port_num, this);
        CS->connect();
//        /// Create a message to join lobby, converting QString into stdString
        JoinLobby *jl = new JoinLobby(userID.toStdString());
        CS->send(jl);
        /**< 1 player emergency backup */
        /**< 1 player emergency backup */

        chatwindow = new chat();
        chatwindow->setClientSocket(CS);
        chatwindow->show(); /**< Show the chat */


    }
}

/**
 * @brief client_GUI::on_input_IP_returnPressed
 * Shortcut: on enter, simulate create button pressed
 */
void client_GUI::on_input_IP_returnPressed()
{
    on_creategameButton_clicked();
}


/**
 * ------------------------------------------------
 * UI page_3: Host lobby
 * ------------------------------------------------
 */
/** Abandon game: Go to page_1 from page_3 */
void client_GUI::on_backto_page_1_f3_clicked()
{
    delete chatwindow;
    delete CS;
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief client_GUI::on_kickButton_clicked
 * Kick player from lobby
 */
void client_GUI::on_kickButton_clicked()
{
    QList<QListWidgetItem*> players_selected = ui->player_list->selectedItems();
    if (players_selected.length()>0) /**< Ensure something selected */
    {
        QListWidgetItem *player_chosen = players_selected[0]; /**< player chosen to kick */
        if (player_chosen->text() != userID)  /**< Ensure chosen is not self */
        {
            delete player_chosen;
        }
    }
}


/**
 * @brief client_GUI::on_startgameButton_clicked
 * Start the game, go into GoFish GUI, server lets other players call their start_GoFish() too.
 */
void client_GUI::on_startgameButton_clicked()
{
//    if (gameChosen == "Go Fish") {
//        start_GoFish();
//    }
//    else if (gameChosen == "Nim") {
//        delete chatwindow;
//        server->
//        start_Nim();
//    }
    GameStart message(42);
    server->socket->broadcast(&message);
}

/**
 * ------------------------------------------------
 * UI page_4: Joining
 * ------------------------------------------------
 */

/** Back to Host/Join: Go to page_1 from page_4 */
void client_GUI::on_backto_page_1_f4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/**
 * @brief client_GUI::on_input_hostaddr_returnPressed
 * On input completion, try to join host with input addr
 */
void client_GUI::on_input_hostaddr_returnPressed()
{
    QString tojoin_hostaddr = ui->input_hostaddr->text(); /**< set the input to tojoin_hostaddr */
    if (tojoin_hostaddr.length()>0) /**< check nonempty */
    {
        ui->join_status->setText(tojoin_hostaddr);
        /// if fail, prompt; if joined, go into waiting screen for host approval, then to page_5
        /// clear player_list, keep listening from host for dynamic update
        ui->player_list_joined->clear();



        /// Create a client Socket with the hostaddr, and a port

        CS = new Socket(tojoin_hostaddr.toStdString().c_str(), port_num, this);
        CS->connect();

        /// Create a message to join lobby, converting QString into stdString
        JoinLobby *jl = new JoinLobby(userID.toStdString());
        CS->send(jl);

        chatwindow = new chat();
        chatwindow->setClientSocket(CS);
        chatwindow->show(); /**< Show the chat */



        ui->stackedWidget->setCurrentIndex(5); /**< go to page_5 joined lobby */
    }


}
/**
 * @brief client_GUI::on_searchjoinButton_clicked
 * Dummy button for joining host with addr
 */
void client_GUI::on_searchjoinButton_clicked()
{
    on_input_hostaddr_returnPressed();
}

/**
 * ------------------------------------------------
 * UI page_5: Joined lobby
 * ------------------------------------------------
 */
/** Leave: Back to host/join: page_1 from page_5 */
void client_GUI::on_backto_page_1_f5_clicked()
{
    /// terminate connection
    delete chatwindow;
    delete CS;
    on_backto_page_1_f4_clicked(); /**< shorthand, call the back button */

}





/**
 * ------------------------------------------------
 * External methods: used by other classes
 * ------------------------------------------------
 */
/**
 * @brief client_GUI::on_promptButton_clicked
 * A sample method to prompt
 */
void client_GUI::on_promptButton_clicked()
{
///    template for creating prompt dialog box
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int res = msgBox.exec();

    if (res == QMessageBox::Save) {
        on_backto_page_1_f4_clicked();
    }
}



/**
 * @brief client_GUI::start_GoFish
 * Once permitted, creates a new instance of goFish_GUI, show it, hide client.
 */
void client_GUI::start_GoFish()
{

    goFish_GUI *instance = new goFish_GUI();
    instance->show(); /**< Show the goFish_GUI */
    this->hide(); /**< Hide this client GUI */
}
/**
 * @brief client_GUI::start_Nim
 * Once permitted, creates a new instance of Nim_GUI, show it, hide client.
 */
void client_GUI::start_Nim()
{
//    server->startGame();
    /**< 1 player emergency backup */
    /**< 1 player emergency backup */
    nimwindow = new Nim_GUI();
    nimwindow->setClientSocket(CS);

//    nimwindow->setPapa(this);
    nimwindow->show(); /**< Show the Nim_GUI */
    this->hide(); /**< Hide this client GUI */
    /**< 1 player emergency backup */
    /**< 1 player emergency backup */

}

/**
 * @brief client_GUI::showSelf
 * When the game ends and closes, show the client GUI directed to page 0
 */
void client_GUI::showSelf()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->show();
//    if (gameChosen == "Go Fish") {
//        start_GoFish();
//    }
//    else if (gameChosen == "Nim") {
//        start_Nim();
//    }
}


/**
 * @brief client_GUI::handle
 * Update the player list in Joined lobby/host lobby
 */
void client_GUI::handle(UpdateLobby *msg)
{
    /// clear player list in joined and host lobbies
    ui->player_list->clear();
    ui->player_list_joined->clear();
    /// readd current players
    QListWidgetItem *item, *item2;
    cout << "trying to update lobby" << endl;
    for (auto it = msg->playerlist.begin(); it != msg->playerlist.end(); ++it)
    {
        item = new QListWidgetItem(QString::fromStdString(*it));
        item2 = new QListWidgetItem(QString::fromStdString(*it));
        cout << "in the loop:" << item->text().toStdString() << endl;
        ui->player_list_joined->addItem(item);
        ui->player_list->addItem(item2);
        cout << "done with one" << endl;
    }
}
/**
 * @brief client_GUI::handle Handles a successful join lobby message from the server.
 * @param message contains the type of game that will be played.
 */
void client_GUI::handle(JoinLobbySuccess *message)
{
    //auto func = clientFunctions[message->gameType];
//    game = func(CS);

}


/**
 * @brief client_GUI::handle
 * Update the chat messages
 */
void client_GUI::handle(ChatIncoming *msg)
{
    cout << "trying to update chat" << endl;
    chatwindow-> addChatString(msg->chatString);
}

/**
 * @brief client_GUI::handle
 * Update the chat messages
 */
void client_GUI::handle(NimIncoming *msg)
{
    cout << "trying to update nimincoming" << endl;
    vector<string> *v3 = new vector<string>();
    v3->push_back(msg->msg);
    string name = "Keng";
    bool your_turn = true;
    cout << "trying to refresh nim screen" << msg->stoneRemain << msg->msg << name << your_turn << endl;

    //    Test: call the refresh screen method
    //cout << "Handler thread: " << std::this_thread::get_id() << endl;
    qRegisterMetaType<string>();
    qRegisterMetaType<vector<string>*>();
    QMetaObject::invokeMethod(nimwindow, "refresh_screen", Qt::QueuedConnection,
                              Q_ARG(int, msg->stoneTaken),
                              Q_ARG(int, msg->stoneRemain),
                              Q_ARG(vector<string>*, v3),
                              Q_ARG(string, name),
                              Q_ARG(bool, your_turn));
    //nimwindow->refresh_screen(msg->stoneTaken, msg->stoneRemain, v3, name, your_turn);
//    vector<string> *v3 = new vector<string>();
//    v3->push_back("The game begins!");
//    string name = "Keng";
//    bool your_turn = true;
//    ui->game_log->clear();

//    //    Test: call the refresh screen method
//    nimwindow->refresh_screen(100, v3, name, your_turn);
}

void client_GUI::handle(GameStart *) {
    QMetaObject::invokeMethod(this, "start_Nim", Qt::QueuedConnection);
}


std::map<std::string, client_GUI::Silliness> client_GUI::serverFunctions = { { "Nim", &(client_GUI::makeServer<GameServer>) }, { "Go Fish", &(client_GUI::makeServer<GameServer>) } };
std::map<std::string, client_GUI::ClientSilliness> client_GUI::clientFunctions = { { "Nim", &(client_GUI::makeGame<Nim>) }, { "Go Fish", &(client_GUI::makeGame<Nim>) } };

