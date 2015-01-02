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
#include <iostream>
#include "application.h"
#include "mainwindow.h"
#include "mellowplayer.h"
#include "pluginsmanager.h"


//---------------------------------------------------------s
MellowPlayerApp::MellowPlayerApp(int &argc, char **argv):
    QApplication(argc, argv),
    mainWindow(NULL)
{
#ifdef __kde_support__
    qDebug() << "MellowPlayer built with KDE support";
#endif
    this->setOrganizationName("MellowPlayer");
    this->setOrganizationDomain("org.mellowplayer");
    this->setApplicationVersion(
        QString("%1.%2.%3%4").arg(
            QString::number(VERSION_MAJOR),
            QString::number(VERSION_MINOR),
            QString::number(VERSION_PATCH),
            VERSION_STATUS));
    singleInstanceController.start(this);
}

//---------------------------------------------------------
MellowPlayerApp::~MellowPlayerApp()
{
    if(mainWindow)
        delete mainWindow;
}

//---------------------------------------------------------
void MellowPlayerApp::initialize()
{
    qDebug() << "Initializing application";
    this->mainWindow = new MainWindow();
    Services::_setMainWindow(this->mainWindow);
    Services::_setCloudServicesManager(new CloudServicesManager(this));
    Services::_setExtensionsManager(new ExtensionsManager(this));
    Services::_setPlayer(new PlayerInterface(this));
    loadPlugins();
    if(Services::cloudServices()->startService("Grooveshark"))
        this->mainWindow->showWebPage();
    else
        this->mainWindow->showHomePage();
    Services::mainWindow()->show();
}

//---------------------------------------------------------
void MellowPlayerApp::raise()
{
    QMainWindow* window = Services::mainWindow();
    window->show();
    window->raise();
    window->activateWindow();
}

//---------------------------------------------------------
int MellowPlayerApp::exec()
{
    int retCode = QApplication::exec();
    this->mainWindow->saveGeometryAndState();
    return retCode;
}
