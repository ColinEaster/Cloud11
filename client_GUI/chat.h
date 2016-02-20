#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include "clientgui_message.h"
#include "../server/messages.h"
#include "../server/clientsocket.h"
#include "../server/messagehandler.h"
#include <string>

using namespace std;

namespace Ui {
class chat;
}

class chat : public QWidget
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = 0);
    ~chat();
    void setClientSocket(Socket *parentCS);
    void addChatString(string chatString);
    void handle(ChatIncoming *msg);

private slots:
    void on_input_asked_returnPressed();

private:
    Ui::chat *ui;
    Socket *CS; /**< socket from parent client GUI */
};

#endif // CHAT_H
