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
#include "cookiejar.h"


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

    bool quit = parseArgs();

    if(!quit)
    {
        connect(this, SIGNAL(commitDataRequest(QSessionManager&)),
                this, SLOT(onCommitDataRequested(QSessionManager&)));

        QString locale = QLocale::system().name().split("_")[0];
        m_translator.load(QString(":/translations/mellowplayer_%1.qm").arg(locale));
        installTranslator(&m_translator);
        m_singleInstanceController.start(this);
    }
    else
        QTimer::singleShot(1, this, SLOT(quit()));
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

    m_mainWindow = new MainWindow(m_debug);

    Services::_setMainWindow(m_mainWindow);
    Services::_setServicesManager(new StreamingServicesManager(this));
    Services::_setExtensionsManager(new ExtensionsManager(this));
    Services::_setPlayer(new PlayerInterface(this));
    loadPlugins();
    m_mainWindow->showWebPage();
    Services::mainWindow()->show();
    if(Services::streamingServices()->startService(m_service))
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

//---------------------------------------------------------
void MellowPlayerApp::onCommitDataRequested(QSessionManager &manager)
{
    Q_UNUSED(manager);
    m_mainWindow->hide();
}

//---------------------------------------------------------
bool MellowPlayerApp::parseArgs()
{
    QStringList args = arguments();
    bool quit = false;
#ifdef QT_DEBUG
    m_debug = true;
#else
    m_debug = false;
#endif
    int autoQuitDelay = 0;
    m_service = QSettings().value("service", "").toString();
    QRegExp rxArgAutoQuit("--autoquit-delay=([0-9]{1,})");
    QRegExp rxArgDebug("--debug");
    QRegExp rxArgHelp("--help");
    QRegExp rxArgVersion("--version");
    QRegExp rxArgClearCookies("--clear-cookies");
    QRegExp rxArgClearSettings("--clear-settings");
    QRegExp rxArgService("--service=([a-zA-Z\\s]*)");

    for (int i = 1; i < args.size(); ++i) {
        if (rxArgAutoQuit.indexIn(args.at(i)) != -1 ) {
            autoQuitDelay =  rxArgAutoQuit.cap(1).toInt();
            QTimer::singleShot(autoQuitDelay * 1000, this, SLOT(quit()));
        }
        else if (rxArgDebug.indexIn(args.at(i)) != -1 ) {
            m_debug = true;
        }
        else if (rxArgClearCookies.indexIn(args.at(i)) != -1 ) {
            qDebug() << "clearing cookies";
            CookieJar().purgeCookies();
        }
        else if (rxArgClearSettings.indexIn(args.at(i)) != -1 ) {
            qDebug() << "clearing settings";
            QSettings().clear();
            m_service = "";
        }
        else if (rxArgHelp.indexIn(args.at(i)) != -1 ) {
            std::cout << "Add cloud music integration to your desktop!" << std::endl << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  * --debug: enable the web inspector"  << std::endl;
            std::cout << "  * --help: show this help message"  << std::endl;
            std::cout << "  * --version: show the version"  << std::endl;
            std::cout << "  * --clear-settings: clear the application settings, restore factory defaults"  << std::endl;
            std::cout << "  * --clear-cookies: clear the stored cookies"  << std::endl;
            std::cout << "  * --version: show the version"  << std::endl;
            std::cout << "  * --service=%s: select a specific service (deezer, grooveshark, groovesharkmobile, mixcloud)"  << std::endl;
            std::cout << "  * --autoquit-delay=%d: a delay for automatically quitting the application (for testing purposes)."  << std::endl;

            quit = true;
        }
        else if (rxArgVersion.indexIn(args.at(i)) != -1 ) {
            std::cout << "MellowPlayer v" << applicationVersion().toStdString() << std::endl;
            quit = true;
        }
        else if (rxArgService.indexIn(args.at(i)) != -1 ) {
            m_service =  rxArgService.cap(1);
        }
        else {
            qDebug() << "Unknown arg:" << args.at(i);
        }
    }

    return quit;
}
