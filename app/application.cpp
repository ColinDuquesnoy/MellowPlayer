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


//---------------------------------------------------------
MellowPlayerApp::MellowPlayerApp(int &argc, char **argv):
    QApplication(argc, argv),
    m_mainWindow(NULL)
{
#ifdef __kde_support__
    qDebug() << "MellowPlayer built with KDE support";
#endif
    setOrganizationName("MellowPlayer");
    setOrganizationDomain("org.mellowplayer");
    setApplicationVersion(
        QString("%1.%2.%3%4").arg(
            QString::number(VERSION_MAJOR),
            QString::number(VERSION_MINOR),
            QString::number(VERSION_MICRO),
            VERSION_STATUS));

    QString locale = QLocale::system().name().split("_")[0];
    qDebug() << "Setting up translations for locale: " << locale;
    m_translator.load(QString(":/translations/mellowplayer_%1.qm").arg(locale));
    installTranslator(&m_translator);
    m_singleInstanceController.start(this);
}

//---------------------------------------------------------
MellowPlayerApp::~MellowPlayerApp()
{
    if(m_mainWindow)
        delete m_mainWindow;
}

//---------------------------------------------------------
void MellowPlayerApp::initialize()
{
    qDebug() << "Initializing application";

    m_mainWindow = new MainWindow();

    Services::_setMainWindow(m_mainWindow);
    Services::_setServicesManager(new StreamingServicesManager(this));
    Services::_setExtensionsManager(new ExtensionsManager(this));
    Services::_setPlayer(new PlayerInterface(this));
    loadPlugins();
    Services::mainWindow()->show();
    if(Services::streamingServices()->startService(
            QSettings().value("service", "").toString()))
        m_mainWindow->showWebPage();
    else
        m_mainWindow->showHomePage();
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
    close();
    if(m_mainWindow)
        m_mainWindow->saveGeometryAndState();
    return retCode;
}

//---------------------------------------------------------
void MellowPlayerApp::close()
{
    if(Services::extensions())
        Services::extensions()->teardown();
    m_singleInstanceController.close();
}
