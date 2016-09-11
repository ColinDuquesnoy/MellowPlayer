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
#include "application.h"
#include "controllers/player.h"
#include "controllers/services.h"
#include "ui_mainwindow.h"
#include "utils/icons.h"
#include "views/mainwindow.h"
#include <QSessionManager>
#include <iostream>
#include <QCommandLineParser>

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
MellowPlayerApp::MellowPlayerApp(int &argc, char **argv)
    : QApplication(argc, argv), m_mainWindow(NULL), m_quit(false) {
  setOrganizationDomain("org.mellowplayer");
  setApplicationDisplayName("MellowPlayer");
  setApplicationName("MellowPlayer");
  setApplicationVersion(APP_VERSION);

  QVersionNumber version = QVersionNumber::fromString(APP_VERSION);

  connect(&m_singleInstanceController,
          &SingleInstanceController::playPauseRequested, this,
          &MellowPlayerApp::onPlayPauseRequested);
  connect(&m_singleInstanceController, &SingleInstanceController::nextRequested,
          this, &MellowPlayerApp::onNextRequested);
  connect(&m_singleInstanceController,
          &SingleInstanceController::previousRequested, this,
          &MellowPlayerApp::onPreviousRequested);

  parseArgs();

  connect(this, SIGNAL(commitDataRequest(QSessionManager &)), this,
          SLOT(onCommitDataRequested(QSessionManager &)));

  QString locale = QLocale::system().name().split("_")[0];
  m_translator.load(QString(":/translations/mellowplayer_%1.qm").arg(locale));
  installTranslator(&m_translator);
  m_singleInstanceController.start(this, applicationDisplayName(), m_action);
}

//--------------------------------------
MellowPlayerApp::~MellowPlayerApp() {
  if (m_mainWindow != nullptr) {
    delete m_mainWindow;
    m_mainWindow = nullptr;
  }
}

//--------------------------------------
void MellowPlayerApp::initialize() {
  if(m_quit)
      return;
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
  if(m_quit)
      return 0;
  // clear covers cache
  QString cacheDir =
      QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0] +
      QDir::separator() + "Covers";
  QDir(cacheDir).removeRecursively();
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
void MellowPlayerApp::parseArgs() {
  QStringList args = arguments();

  QCommandLineParser parser;
  QCommandLineOption helpOption = parser.addHelpOption();
  QCommandLineOption versionOption = parser.addVersionOption();

  QCommandLineOption autoQuitDelayOption("autoquit-delay", "Specifies a delay for automatically quitting the application.", "value", "0");
  parser.addOption(autoQuitDelayOption);

  QCommandLineOption standaloneOption("standalone", "Makes the specified service a standalone application. "
                                                    "This option is ignored if --service hasn't been set");
  parser.addOption(standaloneOption);

  QCommandLineOption serviceOption("service", "Selects a specific service, e.g. deezer, mixcloud, soundcloud, spotify, ...", "service", "");
  parser.addOption(serviceOption);

  QCommandLineOption playPauseOption("playpause", "Plays or pauses the player.");
  parser.addOption(playPauseOption);

  QCommandLineOption nextOption("next", "Skips to the next song.");
  parser.addOption(nextOption);

  QCommandLineOption previousOption("previous", "Skips to the previous song.");
  parser.addOption(previousOption);

  m_service = QSettings().value("services/current", "").toString();
  m_standalone = false;
  m_action = "Restore";

  parser.parse(qApp->arguments());

  if(parser.isSet(helpOption)) {
      std::cout << parser.helpText().toStdString();
      m_quit = true;
  }

  if(parser.isSet(versionOption)) {
      std::cout << "MellowPlayer v"<< qApp->applicationVersion().toStdString() << std::endl;
      m_quit = true;
  }

  if(parser.isSet(autoQuitDelayOption)) {
    int autoQuitDelay = parser.value(autoQuitDelayOption).toInt();
    QTimer::singleShot(autoQuitDelay * 1000, this, SLOT(quit()));
  }

  if(parser.isSet(serviceOption)) {
      m_service = parser.value(serviceOption).replace("_", " ");
  }

  if(parser.isSet(standaloneOption)) {
      m_standalone = true;
  }

  if(parser.isSet(playPauseOption)) {
      m_action = "PlayPause";
  } else if(parser.isSet(nextOption)) {
      m_action = "Next";
  } else if(parser.isSet(previousOption)) {
      m_action = "Previous";
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
  } else if (m_standalone && m_service.isEmpty()) {
    m_standalone = false; // require a --service option
    qWarning() << "--standalone option ignored, require --service to be defined";
  }
}
