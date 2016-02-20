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
#include <QApplication>
#include "client_gui.h"
#include "gofish_gui.h"
#include "nim_gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //cout << "Main thread: " << std::this_thread::get_id() << endl;
    client_GUI w;
    w.show();
//    goFish_GUI g;
//    g.show();
//    Nim_GUI n;
//    n.show();

    return a.exec();
}
