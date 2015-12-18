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

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QtCore>
#include <QtNetwork>
#include "controllers/base.h"
#include "utils/playerinfo.h"
#include "utils/songinfo.h"

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
class MainWindow;
class WebView;

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
/**
 * @brief Controls the webplayer of the current service.
 */
class PlayerController : public BaseController {
  Q_OBJECT
public:
  explicit PlayerController(MainWindow *parent = 0);

  /**
   * @brief Starts polling timer.
   *
   * Everytime the timer timeouts, the song/player infos are updated
   * by running the service plugin javascript code.
   */
  void startPolling();

  /**
   * @brief Stops polling timer, song/player infos won't be updated anymore.
   */
  void stopPolling();

  /**
   * @brief Gets the web player information.
   *
   * @return PlayerInfo
   */
  const PlayerInfo &playerInfo() const;

  /**
   * @brief Gets the current song info.
   *
   * @return SongInfo
   */
  const SongInfo &songInfo() const;

signals:
  void playerCapsChanged(const PlayerInfo &playerInfo);
  void playerStatusChanged(PlayerStatus status);
  void volumeChanged(float newVolume);
  void songChanged(const SongInfo &songInfo);
  void songPositionChanged(double position);
  void songArtReady(const QString &localPath);
  void songDurationAvailable(const SongInfo &songInfo);

public slots:
  void update();
  void playPause();
  void next();
  void previous();
  void addToFavorites();
  void removeFromFavorites();
  void setVolume(float value);
  void seekToPosition(qlonglong position);

private slots:
  void onFavoriteChanged(bool favorite);
  void play();
  void pause();
  void onUpdateFinished(const QVariant &result);
  void onDownloadFinished(QNetworkReply *reply);
  void downloadArtUrl(const SongInfo &songInfo);

private:
  QTimer *m_pollingTimer;
  WebView *m_webView;
  PlayerInfo m_playerInfo;
  SongInfo m_songInfo;
  QNetworkAccessManager *m_nam;
};

#endif // PLAYERCONTROLLER_H
