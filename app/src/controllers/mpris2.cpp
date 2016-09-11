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
#include "controllers/mpris2.h"
#include <QApplication>
#ifdef Q_OS_LINUX
#include "utils/mpris2player.h"
#include "utils/mpris2root.h"
#endif

#define SERVICE_NAME "org.mpris.MediaPlayer2.%1"
#define OBJECT_NAME "/org/mpris/MediaPlayer2"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
MPRIS2Controller::MPRIS2Controller(MainWindow *mainWindow)
    : BaseController("mpris2", mainWindow) {
  QString appName = qApp->applicationDisplayName().replace(" ", "");
  if (appName != "MellowPlayer")
    appName = QString("MellowPlayer-%1").arg((appName));
  m_svName = QString(SERVICE_NAME).arg(appName);
#ifdef Q_OS_LINUX
  if (!QDBusConnection::sessionBus().registerService(m_svName)) {
    qWarning() << "Failed to register service on the session bus: " << m_svName;
    return;
  }
  Mpris2Root *root = new Mpris2Root(this);
  root->setMainWindow(mainWindow);
  Mpris2Player *player = new Mpris2Player(this);
  player->setMainWindow(mainWindow);
  if (!QDBusConnection::sessionBus().registerObject(OBJECT_NAME, this)) {
    qWarning() << "Failed to register object on the session bus: "
               << OBJECT_NAME;
    return;
  }
  qDebug() << "MPRIS2 service started:" << m_svName;
#endif
}

MPRIS2Controller::~MPRIS2Controller() {
#ifdef Q_OS_LINUX
  QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
  QDBusConnection::sessionBus().unregisterObject(m_svName);
#endif
}
