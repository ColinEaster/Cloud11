#include <iostream>
#include <QApplication>
#include "client_controller.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    ClientController controller;

    return a.exec();
}
