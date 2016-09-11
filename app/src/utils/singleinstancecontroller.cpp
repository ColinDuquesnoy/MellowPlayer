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
#include "utils/singleinstancecontroller.h"
#include "application.h"

#ifdef Q_OS_UNIX
#include <signal.h>
#include <unistd.h>
#endif

//---------------------------------------------------------
// Definitions
//---------------------------------------------------------
#define APP_NAME "MellowPlayer"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
SingleInstanceController::SingleInstanceController(QObject *parent)
    : QObject(parent), m_localSocket(new QLocalSocket()),
      m_localServer(new QLocalServer()), m_app(NULL) {
  connect(m_localSocket, SIGNAL(connected()), this, SLOT(onSocketConnected()));

  connect(m_localServer, SIGNAL(newConnection()), this,
          SLOT(onNewConnection()));

  connect(m_localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)), this,
          SLOT(onSocketError()));
}

//--------------------------------------
SingleInstanceController::~SingleInstanceController() {
  delete m_localServer;
  delete m_localSocket;
}

//--------------------------------------
void SingleInstanceController::start(MellowPlayerApp *app,
                                     const QString &appName,
                                     const QString &actionName) {
  m_app = app;
  m_appName = appName;
  m_action = actionName;
#ifndef QT_DEBUG
  m_localSocket->connectToServer(appName, QIODevice::WriteOnly);
#else
  app->initialize();
#endif
}

//--------------------------------------
void SingleInstanceController::close() { m_localServer->close(); }

//--------------------------------------
void SingleInstanceController::onSocketConnected() {
  if (!m_action.isEmpty()) {
    m_localSocket->write(QString(m_action + "\n").toLocal8Bit());
  }
  // This means the server is already running and we have to exit.
  qDebug() << "Another instance is already running, quitting...";
  QTimer::singleShot(1000, m_app, SLOT(quit()));
}

//--------------------------------------
void SingleInstanceController::onSocketError() {
  if (!m_localServer->listen(m_appName))
    qWarning() << "Failed to start local server, cannot ensure unique "
                  "application instance";
  connectSignalHandlers();
  m_app->initialize();
}

//--------------------------------------
void SingleInstanceController::onNewConnection() {
  QLocalSocket *socket = m_localServer->nextPendingConnection();

  connect(socket, &QLocalSocket::readyRead, this,
          &SingleInstanceController::onReadyRead);
}

//--------------------------------------
void SingleInstanceController::onReadyRead() {
  QLocalSocket *socket = static_cast<QLocalSocket *>(sender());
  QStringList actions = QString(socket->readAll()).split("\n");
  foreach (const QString &a, actions) {
    if (a == "PlayPause") {
      emit playPauseRequested();
    } else if (a == "Next") {
      emit nextRequested();
    } else if (a == "Previous") {
      emit previousRequested();
    } else if (a == "Restore") {
      m_app->raise();
    }
  }
}

void SingleInstanceController::connectSignalHandlers()
{
#ifdef Q_OS_UNIX
    auto handler = [](int sig) ->void {
      printf("\nquit the application (user request signal = %d).\n", sig);
      QFile::remove("/tmp/MellowPlayer");
      QCoreApplication::quit();
    };
    QList<int> unix_signals = {SIGKILL, SIGTERM, SIGQUIT, SIGINT};
    foreach (int sig, unix_signals) {
      signal(sig, handler);
    }
#endif
}
