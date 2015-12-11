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
#include "views/mainwindow.h"
#include "utils/mpris2root.h"
#include "ui_mainwindow.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
Mpris2Root::Mpris2Root(QObject *parent) : QDBusAbstractAdaptor(parent) {}

//--------------------------------------
void Mpris2Root::setMainWindow(MainWindow *mainWindow) {
  m_mainWindow = mainWindow;
}

//-------------------------------------
void Mpris2Root::Raise() { m_mainWindow->restoreWindow(); }

//-------------------------------------
void Mpris2Root::Quit() { qApp->exit(0); }

//-------------------------------------
bool Mpris2Root::canRaise() { return true; }

//-------------------------------------
bool Mpris2Root::canQuit() { return true; }

//-------------------------------------
bool Mpris2Root::hasTrackList() { return false; }

//-------------------------------------
bool Mpris2Root::canSetFullscreen() { return true; }

//-------------------------------------
bool Mpris2Root::fullscreen() { return m_mainWindow->isFullScreen(); }

//-------------------------------------
void Mpris2Root::setFullscreen(bool value) {
  if (value)
    m_mainWindow->showFullScreen();
  else
    m_mainWindow->showNormal();
}

//-------------------------------------
QString Mpris2Root::identity() { return qApp->applicationDisplayName(); }

//-------------------------------------
QString Mpris2Root::desktopEntry() {
  return qApp->applicationDisplayName().toLower();
}

//-------------------------------------
QStringList Mpris2Root::supportedUriSchemes() {
  QStringList retVal;
  retVal.append("http");
  return retVal;
}

//-------------------------------------
QStringList Mpris2Root::supportedMimeTypes() { return QStringList(); }
