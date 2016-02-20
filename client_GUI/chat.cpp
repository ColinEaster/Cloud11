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
#include "chat.h"
#include "ui_chat.h"

/**
 * @brief chat::chat
 * @param parent
 * Constructor
 */
chat::chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    ui->game_log->clear();
    ui->game_log->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->input_asked->setAttribute(Qt::WA_MacShowFocusRect, 0);
}

/**
 * @brief chat::~chat
 * Destructor
 */
chat::~chat()
{
    delete ui;
}

/**
 * @brief chat::setClientSocket
 * @param parentCS
 * Pass the parent Socket from client GUI for it to use.
 */
void chat::setClientSocket(Socket *parentCS)
{
    CS = parentCS;
}

/**
 * @brief chat::on_input_asked_returnPressed
 * On entering chat msg, send message
 */
void chat::on_input_asked_returnPressed()
{
    QString input = ui->input_asked->text(); /**< set the input var */
    if (input.length()>0) /**< check nonempty */
    {
        ChatInput *chatmsg = new ChatInput(input.toStdString());
        CS->send(chatmsg);
        ui->input_asked->clear();
        /**< send chat message */
    }
}

/**
 * @brief chat::addChatString
 * @param chatString
 * External method to add chat string to chat window
 */
void chat::addChatString(string chatString)
{
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(chatString));
    ui->game_log->insertItem(0, item);
    ui->game_log->setCurrentItem(item);
}




