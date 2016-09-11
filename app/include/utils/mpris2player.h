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

#ifndef MPRIS2PLAYER_H
#define MPRIS2PLAYER_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include "controllers/player.h"
#include "utils/playerinfo.h"
#include "utils/songinfo.h"
#include <QObject>
#include <QtDBus>

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
/*!
 * \brief The Mpris2Player class implements the MPRIS Player Interface
 *
 * http://specifications.freedesktop.org/mpris-spec/latest/Player_Interface.html
 */
class Mpris2Player : public QDBusAbstractAdaptor {
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")

public:
  explicit Mpris2Player(QObject *parent = NULL);

  void setMainWindow(MainWindow *mainWindow);

  Q_PROPERTY(QVariantMap Metadata READ metadata)
  Q_PROPERTY(bool CanControl READ canControl)
  Q_PROPERTY(bool CanSeek READ canSeek)
  Q_PROPERTY(bool CanPause READ canPause)
  Q_PROPERTY(bool CanPlay READ canPlay)
  Q_PROPERTY(bool CanStope READ canStop)
  Q_PROPERTY(bool CanGoPrevious READ canGoPrevious)
  Q_PROPERTY(bool CanGoNext READ canGoNext)
  Q_PROPERTY(qlonglong Position READ position)
  Q_PROPERTY(int MinimuRate READ minimumRate)
  Q_PROPERTY(int MaximuRate READ maximumRate)
  Q_PROPERTY(int Rate READ rate WRITE setRate)
  Q_PROPERTY(double Volume READ volume WRITE setVolume)
  Q_PROPERTY(int Shuffle READ shuffle WRITE setShuffle)
  Q_PROPERTY(QString LoopStatus READ loopStatus WRITE setLoopStatus)
  Q_PROPERTY(QString PlaybackStatus READ playbackStatus)

signals:
  void Seeked(qlonglong);

public slots:
  void PlayPause();
  void Play();
  void Pause();
  void Stop();
  void Next();
  void Previous();
  void Seek(qlonglong position);
  void SetPosition(const QDBusObjectPath &trackId, qlonglong position);

private slots:
  void onPlaybackStatusChanged(PlayerStatus status);
  void onSongChanged(const SongInfo &song);
  void onArtReady(const QString &artFilePathUrl);
  void onPositionChanged(double position);
  void onControlCapsChanged(const PlayerInfo &playerInfo);
  void onVolumeChanged(double volume);
  void onServiceStarted(const QString &serviceName);

private:
  QString playbackStatus();
  QString loopStatus();
  void setLoopStatus(const QString &status);
  bool shuffle();
  void setShuffle(bool value);
  double volume();
  void setVolume(double value);
  QVariantMap metadata();
  double minimumRate();
  double maximumRate();
  double rate();
  void setRate(float value);
  qlonglong position();
  bool canGoNext();
  bool canGoPrevious();
  bool canPlay();
  bool canStop();
  bool canPause();
  bool canSeek();
  bool canControl();

  QMap<QString, QVariant> toXesam(const SongInfo &song);
  QString statusToString(PlayerStatus status);
  qlonglong m_length;
  qlonglong m_prevPos;
  MainWindow *m_mainWindow;
  PlayerController *m_player;
  QMap<QString, QVariant> m_lastMeta;
};

#endif // MPRIS2PLAYER_H
