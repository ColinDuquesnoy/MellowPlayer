//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <iostream>
#include <QSessionManager>
#include "application.h"
#include "controllers/player.h"
#include "controllers/services.h"
#include "utils/icons.h"
#include "views/mainwindow.h"
#include "ui_mainwindow.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
MellowPlayerApp::MellowPlayerApp(int &argc, char **argv)
    : QApplication(argc, argv), m_mainWindow(NULL) {
  setOrganizationDomain("org.mellowplayer");
  setApplicationDisplayName("MellowPlayer");
  setApplicationName("MellowPlayer");
  setApplicationVersion(QString("%1.%2.%3")
                            .arg(QString::number(VERSION_MAJOR),
                                 QString::number(VERSION_MINOR),
                                 QString::number(VERSION_MICRO)));

  connect(&m_singleInstanceController,
          &SingleInstanceController::playPauseRequested, this,
          &MellowPlayerApp::onPlayPauseRequested);
  connect(&m_singleInstanceController, &SingleInstanceController::nextRequested,
          this, &MellowPlayerApp::onNextRequested);
  connect(&m_singleInstanceController,
          &SingleInstanceController::previousRequested, this,
          &MellowPlayerApp::onPreviousRequested);

  bool quit = parseArgs();

  if (!quit) {
    connect(this, SIGNAL(commitDataRequest(QSessionManager &)), this,
            SLOT(onCommitDataRequested(QSessionManager &)));

    QString locale = QLocale::system().name().split("_")[0];
    m_translator.load(QString(":/translations/mellowplayer_%1.qm").arg(locale));
    installTranslator(&m_translator);
    m_singleInstanceController.start(this, applicationDisplayName(), m_action);
  } else
    QTimer::singleShot(1, this, SLOT(quit()));
}

//--------------------------------------
MellowPlayerApp::~MellowPlayerApp() {
  if (m_mainWindow)
    delete m_mainWindow;
}

//--------------------------------------
void MellowPlayerApp::initialize() {
  qDebug() << "Initializing application";

  m_mainWindow = new MainWindow();

  if (!m_service.isEmpty()) {
    m_mainWindow->services()->startService(m_service);
  } else {
    m_mainWindow->services()->startService(
        QSettings().value("services/current", "").toString());
  }

  if (m_standalone) {
    const QIcon &webAppIcon = m_mainWindow->services()->currentService().Icon;
    setWindowIcon(webAppIcon);
    m_mainWindow->setWindowIcon(webAppIcon);
    m_mainWindow->ui()->actionSelect_service->setVisible(false);
    m_mainWindow->trayIcon()->setIcon(Icons::trayIcon());
  } else {
    setWindowIcon(m_mainWindow->windowIcon());
    m_mainWindow->trayIcon()->setIcon(Icons::trayIcon());
  }

  if (QSettings().value("interface/showFullscreen", false).toBool())
    m_mainWindow->showFullScreen();
  else
    m_mainWindow->show();
}

//--------------------------------------
void MellowPlayerApp::raise() { m_mainWindow->restoreWindow(); }

//--------------------------------------
int MellowPlayerApp::exec() {
  int retCode = QApplication::exec();
  close();
  if (m_mainWindow)
    m_mainWindow->saveGeometryAndState();
  return retCode;
}

//--------------------------------------
void MellowPlayerApp::close() { m_singleInstanceController.close(); }

//--------------------------------------
void MellowPlayerApp::onCommitDataRequested(QSessionManager &manager) {
  Q_UNUSED(manager);
  m_mainWindow->hide();
}

//--------------------------------------
void MellowPlayerApp::onPlayPauseRequested() {
  m_mainWindow->player()->playPause();
}

//--------------------------------------
void MellowPlayerApp::onNextRequested() { m_mainWindow->player()->next(); }

//--------------------------------------
void MellowPlayerApp::onPreviousRequested() {
  m_mainWindow->player()->previous();
}

//--------------------------------------
bool MellowPlayerApp::parseArgs() {
  QStringList args = arguments();
  bool quit = false;
#ifdef QT_DEBUG
  m_debug = true;
#else
  m_debug = false;
#endif
  int autoQuitDelay = 0;
  m_service = QSettings().value("services/current", "").toString();
  QRegExp rxArgAutoQuit("--autoquit-delay=([0-9]{1,})");
  QRegExp rxArgHelp("--help");
  QRegExp rxArgVersion("--version");
  QRegExp rxArgStandalone("--standalone");
  QRegExp rxArgService("--service=([a-zA-Z\\s_\\d]*)");
  QRegExp rxArgPlayPause("--playpause");
  QRegExp rxArgNext("--next");
  QRegExp rxArgPrevious("--previous");

  m_standalone = false;
  m_action = "Restore";

  for (int i = 1; i < args.size(); ++i) {
    if (rxArgAutoQuit.indexIn(args.at(i)) != -1) {
      autoQuitDelay = rxArgAutoQuit.cap(1).toInt();
      QTimer::singleShot(autoQuitDelay * 1000, this, SLOT(quit()));
    } else if (rxArgHelp.indexIn(args.at(i)) != -1) {
      std::cout << tr("Add cloud music integration to your desktop!")
                       .toStdString() << std::endl
                << std::endl;
      std::cout << tr("Options:").toStdString() << std::endl;
      std::cout << tr("  * --help: show this help message").toStdString()
                << std::endl;
      std::cout << tr("  * --version: show the version").toStdString()
                << std::endl;
      std::cout
          << tr("  * --standalone: make the specified service a standalone "
                "application. (ignored if --service is not used)").toStdString()
          << std::endl;
      std::cout
          << tr("  * --service=%s: select a specific service (e.. deezer, "
                "mixcloud, soundcloud or spotify)").toStdString() << std::endl;
      std::cout << tr("  * --autoquit-delay=%d: a delay for automatically "
                      "quitting the application (for testing purposes).")
                       .toStdString() << std::endl;
      quit = true;
    } else if (rxArgVersion.indexIn(args.at(i)) != -1) {
      std::cout << "MellowPlayer v" << applicationVersion().toStdString()
                << std::endl;
      quit = true;
    } else if (rxArgService.indexIn(args.at(i)) != -1) {
      m_service = rxArgService.cap(1);
      m_service = m_service.replace("_", " ");
    } else if (rxArgStandalone.indexIn(args.at(i)) != -1) {
      m_standalone = true;
    } else if (rxArgPlayPause.indexIn(args.at(i)) != -1) {
      m_action = "PlayPause";
    } else if (rxArgNext.indexIn(args.at(i)) != -1) {
      m_action = "Next";
    } else if (rxArgPrevious.indexIn(args.at(i)) != -1) {
      m_action = "Previous";
    } else {
      qDebug() << "Unknown arg:" << args.at(i);
    }
  }

  if (m_standalone && !m_service.isEmpty()) {
    // capitalize each parts of the service name
    QStringList tokens = m_service.split(" ");
    QStringList capitalized;
    foreach (const QString &t, tokens) {
      capitalized.append(t.left(1).toUpper() + t.mid(1).toLower());
    }
    QString appName = capitalized.join(" ");
    setApplicationDisplayName(appName);
    setApplicationName(appName);
  } else
    m_standalone = false; // require a --service option

  return quit;
}
