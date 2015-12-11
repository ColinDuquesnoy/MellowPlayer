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
#include <QSettings>
#include <QFile>
#include <QApplication>
#include "utils/icons.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
QIcon Icons::play() {
  return QIcon::fromTheme("media-playback-start",
                          QIcon(":/icons/media-playback-start.png"));
}

//--------------------------------------
QIcon Icons::pause() {
  return QIcon::fromTheme("media-playback-pause",
                          QIcon(":/icons/media-playback-pause.png"));
}

//--------------------------------------
QIcon Icons::stop() {
  return QIcon::fromTheme("media-playback-stop",
                          QIcon(":/icons/media-playback-stop.png"));
}

//--------------------------------------
QIcon Icons::next() {
  return QIcon::fromTheme("media-seek-forward",
                          QIcon(":/icons/media-seek-forward.png"));
}

//--------------------------------------
QIcon Icons::previous() {
  return QIcon::fromTheme("media-seek-backward",
                          QIcon(":/icons/media-seek-backward.png"));
}

//--------------------------------------
QIcon Icons::selectStreamingService() {
  return QIcon::fromTheme("system-run", QIcon(":/icons/system-run.png"));
}

//--------------------------------------
QIcon Icons::preferences() {
  return QIcon::fromTheme("preferences-system",
                          QIcon(":/icons/preferences-system.png"));
}

//--------------------------------------
QIcon Icons::quit() {
  return QIcon::fromTheme("application-exit",
                          QIcon(":/icons/application-exit.png"));
}

//--------------------------------------
QIcon Icons::about() {
  return QIcon::fromTheme("help-about", QIcon(":/icons/help-about.png"));
}

//--------------------------------------
QIcon Icons::help() {
  return QIcon::fromTheme("help-contents", QIcon(":/icons/help-contents.png"));
}

//--------------------------------------
QIcon Icons::reportBug() {
  return QIcon::fromTheme("tools-report-bug",
                          QIcon(":/icons/tools-report-bug.png"));
}

//--------------------------------------
QIcon Icons::mellowPlayer() {
  return QIcon::fromTheme("mellowplayer", QIcon(":/icons/mellowplayer.png"));
}

//--------------------------------------
QIcon Icons::interfacePreferences() {
  return QIcon::fromTheme("preferences-desktop-theme",
                          QIcon(":/icons/preferences-desktop-theme.png"));
}

//--------------------------------------
QIcon Icons::shortcuts() {
  return QIcon::fromTheme("preferences-desktop-keyboard",
                          QIcon(":/icons/preferences-desktop-keyboard.png"));
}

//--------------------------------------
QIcon Icons::plugins() {
  return QIcon::fromTheme("preferences-other",
                          QIcon(":/icons/preferences-other.png"));
}

//--------------------------------------
QIcon Icons::userTrash() {
  return QIcon::fromTheme("user-trash", QIcon(":/icons/user-trash.png"));
}

//--------------------------------------
QIcon Icons::favorite() {
  return QIcon::fromTheme("emblem-favorite",
                          QIcon(":/icons/emblem-favorite.png"));
}

//--------------------------------------
QIcon Icons::configure() {
  return QIcon::fromTheme("applications-system",
                          QIcon(":/icons/applications-system.png"));
}

//--------------------------------------
QIcon Icons::back() {
  return QIcon::fromTheme("go-previous", QIcon(":/icons/go-previous.png"));
}

//--------------------------------------
QIcon Icons::forward() {
  return QIcon::fromTheme("go-next", QIcon(":/icons/go-next.png"));
}

//--------------------------------------
QIcon Icons::home() {
  return QIcon::fromTheme("go-home", QIcon(":/icons/go-home.png"));
}

//--------------------------------------
QIcon Icons::reload() {
  return QIcon::fromTheme("view-refresh", QIcon(":/icons/view-refresh.png"));
}

//--------------------------------------
QIcon Icons::trayIcon() {
  QString iconString = QSettings().value("interface/trayIcon").toString();
  if (iconString.trimmed().isEmpty())
    return qApp->windowIcon();
  else if (QFile::exists(iconString))
    return QIcon(iconString);
  else
    return QIcon::fromTheme(iconString);
}

//--------------------------------------
QIcon Icons::notifications() {
  if (QIcon::hasThemeIcon("preferences-desktop-notification")) {
    return QIcon::fromTheme("preferences-desktop-notification");
  } else {
    return QIcon::fromTheme(
        "dialog-information",
        QIcon(":/icons/preferences-desktop-notification.png"));
  }
}
