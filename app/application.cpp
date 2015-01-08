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
    qDebug() << QObject::tr("MellowPlayer built with KDE support");
#endif
    this->setOrganizationName("MellowPlayer");
    this->setOrganizationDomain("org.mellowplayer");
    this->setApplicationVersion(
        QString("%1.%2.%3%4").arg(
            QString::number(VERSION_MAJOR),
            QString::number(VERSION_MINOR),
            QString::number(VERSION_PATCH),
            VERSION_STATUS));

    QChar driveLetter = this->applicationFilePath().at(0);
    QString path_to_translations = QString(driveLetter) + ":/../translations";
//    QString locale = QLocale::system().name();
    QString locale = "fr";
    translator.load("mellowplayer_" + locale, path_to_translations);
    this->installTranslator(&translator);

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
    qDebug() << QObject::tr("Initializing application");
    this->mainWindow = new MainWindow();
    Services::_setMainWindow(this->mainWindow);
    Services::_setCloudServicesManager(new CloudServicesManager(this));
    Services::_setExtensionsManager(new ExtensionsManager(this));
    Services::_setPlayer(new PlayerInterface(this));
    loadPlugins();
    if(Services::cloudServices()->startService(
            QSettings().value("service", "").toString()))
        this->mainWindow->showWebPage();
    else
        this->mainWindow->showHomePage();
    Services::mainWindow()->show();
}

//---------------------------------------------------------
void MellowPlayerApp::raise()
{
    Services::raiseMainWindow();
}

//---------------------------------------------------------
int MellowPlayerApp::exec()
{
    int retCode = QApplication::exec();
    if(this->mainWindow)
        this->mainWindow->saveGeometryAndState();
    if(Services::extensions())
        Services::extensions()->teardown();
    return retCode;
}
