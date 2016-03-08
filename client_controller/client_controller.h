#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <string>
#include <map>
#include "../client_GUI/client_gui.h"

class ClientController: public QObject
{
    Q_OBJECT

public:
    ClientController();
    ~ClientController();

public slots:
    void receiveName(std::string name);
    void receiveIP(std::string ip);
    void receiveHostDecision(bool wantsToHost);

protected:
    client_GUI* clientGUI;

private:
    void startGame(std::string gameName){};
    void mapClientAndServerFunctions(){};

    typedef void (*serverFunction)(int);
    typedef void (*clientFunction)(void);
    std::map<std::string, serverFunction> serverCreationFunctions;
    std::map<std::string, clientFunction> clientGuiCreationFunctions;

    std::string playerName = "";
    std::string ipToConnectTo = "";
    bool isHosting = false;


};

#endif // CLIENTCONTROLLER_H
