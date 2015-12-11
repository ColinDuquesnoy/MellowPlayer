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

#ifndef NOTIFICATIONSCONTROLLER_H
#define NOTIFICATIONSCONTROLLER_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <libsnore/snore.h>
#include "controllers/base.h"
#include "controllers/player.h"

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
class MainWindow;

//---------------------------------------------------------
// AlertTypes
//---------------------------------------------------------
enum class AlertTypes { Default, SongChanged, PlaybackPaused, PlaybackStopped };

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
class NotificationsController : public BaseController {
  Q_OBJECT
public:
  explicit NotificationsController(MainWindow *parent);
  void showMessage(const QString &title, const QString &message,
                   const QIcon &icon = QIcon(),
                   const QStringList &actions = QStringList());
signals:
  void actionTriggered(const QString &actionName);

private slots:
  void onActionInvoked(const Snore::Notification &notification);
  void onPlaybackStatusChanged(PlayerStatus status);
  void onArtReady(const QString &artUrl);
  void showSongChangedNotification(const SongInfo &song);

private:
  Snore::Application m_SnoreApp;
  Snore::Alert m_SongChangedAlert;
  Snore::Alert m_playbackPausedAlert;
  Snore::Alert m_playbackStoppedAlert;
  Snore::Notification m_oldNotification;

  SongInfo m_oldSong;
};

#endif // NOTIFICATIONSCONTROLLER_H
