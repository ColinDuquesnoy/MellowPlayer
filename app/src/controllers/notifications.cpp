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
#include "controllers/notifications.h"
#include "controllers/services.h"
#include "utils/icons.h"
#include "views/mainwindow.h"
#include "ui_mainwindow.h"

#ifndef Q_OS_MAC
using namespace Snore;
#endif

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
NotificationsController::NotificationsController(MainWindow *parent)
    : BaseController("notifications", parent)
{
#ifndef Q_OS_MAC
  m_SnoreApp("MellowPlayer", m_mainWindow->windowIcon());
  m_SongChangedAlert("Song changed", m_mainWindow->windowIcon());
  m_playbackPausedAlert("Paused", Icons::pause());
  m_playbackStoppedAlert("Stopped", Icons::stop());
  SnoreCore &snoreCore = SnoreCore::instance();
  snoreCore.registerApplication(m_SnoreApp);
  snoreCore.setDefaultApplication(m_SnoreApp);
  snoreCore.loadPlugins(Snore::SnorePlugin::ALL);

  qDebug() << "Primary notification backend:"
           << snoreCore.primaryNotificationBackend();
  qDebug() << "Available notification backends:"
           << snoreCore.pluginNames(Snore::SnorePlugin::BACKEND);
  connect(&snoreCore, &SnoreCore::actionInvoked, this,
          &NotificationsController::onActionInvoked);
#endif
  PlayerController *player = m_mainWindow->player();
  connect(player, &PlayerController::playerStatusChanged, this,
          &NotificationsController::onPlaybackStatusChanged);
  connect(player, &PlayerController::songArtReady, this,
          &NotificationsController::onArtReady);
}

//--------------------------------------
void NotificationsController::showMessage(const QString &title,
                                          const QString &message,
                                          const QIcon &icon,
                                          const QStringList &actions) {
  if (!QSettings().value("notifications/enable", true).toBool()) {
    return;
  }
#ifndef Q_OS_MAC
  SnoreCore &snoreCore = SnoreCore::instance();
  QString myTitle = title;
  QString myMessage = message;
  QIcon myIcon = icon;

  if (icon.isNull()) {
    myIcon = m_mainWindow->windowIcon();
  }

  if (!m_SnoreApp.constHints().value("use-markup").toBool()) {
    myTitle = Utils::normalizeMarkup(myTitle, Utils::NO_MARKUP);
    myMessage = Utils::normalizeMarkup(myMessage, Utils::NO_MARKUP);
  }

  int timeout = QSettings().value("notifications/timeout", 5).toInt();

  if (m_oldNotification.isValid() && timeout != 0)
    snoreCore.requestCloseNotification(m_oldNotification,
                                       Notification::REPLACED);

  Notification noti(m_SnoreApp, m_SnoreApp.defaultAlert(), myTitle, myMessage,
                    myIcon, timeout);
  if (QSettings().value("notifications/enableActions", true).toBool()) {
    int i = 1;
    foreach (const QString &actionName, actions) {
      noti.addAction(Action(i, actionName));
      ++i;
    }
  }
  snoreCore.broadcastNotification(noti);
  m_oldNotification = noti;
#else
  m_mainWindow->trayIcon()->showMessage(
    title,
    QTextDocumentFragment::fromHtml(message).toPlainText());
  Q_UNUSED(icon);
  Q_UNUSED(actions);
#endif
}

#ifndef Q_OS_MAC
//--------------------------------------
void NotificationsController::onActionInvoked(
    const Notification &notification) {
  Q_UNUSED(notification)

  QString actionName = notification.actionInvoked().name();

  if (actionName == tr("Open")) {
    m_mainWindow->restoreWindow();
  } else {
    emit actionTriggered(actionName);
  }
}
#endif

//--------------------------------------
void NotificationsController::onPlaybackStatusChanged(PlayerStatus status) {
  const SongInfo &song = m_mainWindow->player()->songInfo();
  const StreamingServicePlugin &sv = m_mainWindow->services()->currentService();
  bool pausedEnabled =
      QSettings().value("notifications/enablePaused", false).toBool();
  bool stoppedEnabled =
      QSettings().value("notifications/enableStopped", false).toBool();
  QStringList actions;
  actions << tr("Open");
  if (status == PlayerStatus::Playing && !song.LocalArtUrl.isEmpty()) {
    showSongChangedNotification(song);
  } else if (status == PlayerStatus::Paused && pausedEnabled)
    showMessage(tr("Paused"), tr("%1 playback paused").arg(sv.Name), sv.Icon,
                actions);
  else if (status == PlayerStatus::Stopped && stoppedEnabled)
    showMessage(tr("Stopped"), tr("%1 playback stopped").arg(sv.Name), sv.Icon,
                actions);
}

//--------------------------------------
void NotificationsController::onArtReady(const QString &artUrl) {
  Q_UNUSED(artUrl);
  const SongInfo &song = m_mainWindow->player()->songInfo();
  const PlayerInfo &player = m_mainWindow->player()->playerInfo();
  if (player.Status == PlayerStatus::Playing) {
    showSongChangedNotification(song);
  }
}

//--------------------------------------
void NotificationsController::showSongChangedNotification(
    const SongInfo &song) {
  if (!song.isValid() || song == m_oldSong)
    return;
  bool songChangedEnabled =
      QSettings().value("notifications/enableSongChanged", true).toBool();
  if (!songChangedEnabled)
    return;
  const StreamingServicePlugin &sv = m_mainWindow->services()->currentService();
  QStringList actions;
  actions << tr("Open");
  showMessage(sv.Name, song.toPrettyString(), QIcon(song.LocalArtUrl), actions);
  m_oldSong = song;
}
