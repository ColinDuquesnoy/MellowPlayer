//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------
#include "application.h"
#include "mainwindow.h"



//---------------------------------------------------------s
MellowPlayerApp::MellowPlayerApp(int &argc, char **argv):
    QApplication(argc, argv),
    window(NULL)
{
    singleInstanceController.start(this);
}

//---------------------------------------------------------
MellowPlayerApp::~MellowPlayerApp()
{
    if(window)
        delete this->window;
}

//---------------------------------------------------------
void MellowPlayerApp::initialize()
{
    qDebug() << "Initializing application";
    this->window = new MainWindow();
    this->window->show();
}

//---------------------------------------------------------
void MellowPlayerApp::raise()
{
    this->window->show();
    this->window->raise();
    this->window->activateWindow();
}

