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
#include "utils/mpris2player.h"
#include "controllers/services.h"
#include "ui_mainwindow.h"
#include "utils/mpris_utils.h"
#include "views/mainwindow.h"
#include <math.h>

#define SEC_TO_MICROSEC 1000000
#define SEEK_DELTA_LIMIT SEC_TO_MICROSEC * 2

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
Mpris2Player::Mpris2Player(QObject *parent)
    : QDBusAbstractAdaptor(parent), m_prevPos(0) {}

//-------------------------------------
void Mpris2Player::setMainWindow(MainWindow *mainWindow) {
  m_mainWindow = mainWindow;
  m_player = mainWindow->player();
  StreamingServicesController *services = mainWindow->services();

  connect(m_player, &PlayerController::playerStatusChanged, this,
          &Mpris2Player::onPlaybackStatusChanged);
  connect(m_player, &PlayerController::songChanged, this,
          &Mpris2Player::onSongChanged);
  connect(m_player, &PlayerController::songArtReady, this,
          &Mpris2Player::onArtReady);
  connect(m_player, &PlayerController::songPositionChanged, this,
          &Mpris2Player::onPositionChanged);
  connect(m_player, &PlayerController::playerCapsChanged, this,
          &Mpris2Player::onControlCapsChanged);
  connect(m_player, &PlayerController::volumeChanged, this,
          &Mpris2Player::onVolumeChanged);
  connect(m_player, &PlayerController::songDurationAvailable, this,
          &Mpris2Player::onSongChanged);
  connect(services, &StreamingServicesController::serviceStarted, this,
          &Mpris2Player::onServiceStarted);
}

//-------------------------------------
void Mpris2Player::PlayPause() { m_player->playPause(); }

//-------------------------------------
void Mpris2Player::Play() { m_player->playPause(); }

//-------------------------------------
void Mpris2Player::Pause() { m_player->playPause(); }

//-------------------------------------
void Mpris2Player::Stop() { Pause(); }

//-------------------------------------
void Mpris2Player::Next() { m_player->next(); }

//-------------------------------------
void Mpris2Player::Previous() { m_player->previous(); }

//-------------------------------------
void Mpris2Player::Seek(qlonglong position) {
  qlonglong newPos = this->position() + position;
  m_prevPos = 0; // force emit seeked
  m_player->seekToPosition(newPos / SEC_TO_MICROSEC);
}

//-------------------------------------
void Mpris2Player::SetPosition(const QDBusObjectPath &trackId,
                               qlonglong position) {
  Q_UNUSED(trackId);
  m_prevPos = 0; // force emit seeked
  m_player->seekToPosition(position / SEC_TO_MICROSEC);
}

//-------------------------------------
void Mpris2Player::onPlaybackStatusChanged(PlayerStatus status) {
  Q_UNUSED(status);
  QVariantMap map;
  map["PlaybackStatus"] = statusToString(status);
  signalPlayerUpdate(map);
}

//-------------------------------------
void Mpris2Player::onSongChanged(const SongInfo &song) {
  QVariantMap map;
  map["Metadata"] = toXesam(song);
  if (map != m_lastMeta)
    signalPlayerUpdate(map);
  m_lastMeta = map;
}

//-------------------------------------
void Mpris2Player::onArtReady(const QString &artFilePathUrl) {
  Q_UNUSED(artFilePathUrl);
  QVariantMap map;
  map["Metadata"] = toXesam(m_player->songInfo());
  if (map != m_lastMeta)
    signalPlayerUpdate(map);
  m_lastMeta = map;
}

//-------------------------------------
void Mpris2Player::onPositionChanged(double position) {
  qlonglong pos = (qlonglong)position * SEC_TO_MICROSEC;
  if (abs(pos - m_prevPos) > SEEK_DELTA_LIMIT || (m_prevPos == 0 && pos > 0))
    emit Seeked(pos);
  m_prevPos = pos;
}

//-------------------------------------
void Mpris2Player::onControlCapsChanged(const PlayerInfo &playerInfo) {
  QVariantMap map;
  map["CanSeek"] = playerInfo.CanSeek;
  map["CanGoNext"] = playerInfo.CanGoNext;
  map["CanGoPrevious"] = playerInfo.CanGoPrevious;
  signalPlayerUpdate(map);
}

//-------------------------------------
void Mpris2Player::onVolumeChanged(double volume) {
  QVariantMap map;
  map["Volume"] = volume;
  signalPlayerUpdate(map);
}

//-------------------------------------
void Mpris2Player::onServiceStarted(const QString &serviceName) {
  Q_UNUSED(serviceName);
  this->onControlCapsChanged(m_player->playerInfo());
  this->onSongChanged(SongInfo());
  this->onPlaybackStatusChanged(PlayerStatus::Stopped);
}

//-------------------------------------
QString Mpris2Player::playbackStatus() {
  PlayerStatus status = m_player->playerInfo().Status;
  return statusToString(status);
}

//-------------------------------------
QString Mpris2Player::statusToString(PlayerStatus status) {
  // a player that is buffering is considered to be paused for mpris,
  // othersie the player disappear on Plasma 5.
  if (status == PlayerStatus::Buffering)
    status = PlayerStatus::Paused;
  switch (status) {
  case PlayerStatus::Playing:
    return "Playing";
  case PlayerStatus::Paused:
    return "Paused";
  default:
    return "Stopped";
  }
}

//-------------------------------------
QString Mpris2Player::loopStatus() { return "None"; }

//-------------------------------------
void Mpris2Player::setLoopStatus(const QString &status) { Q_UNUSED(status); }

//-------------------------------------
bool Mpris2Player::shuffle() { return false; }

//-------------------------------------
void Mpris2Player::setShuffle(bool value) { Q_UNUSED(value); }

//-------------------------------------
double Mpris2Player::volume() { return m_player->playerInfo().Volume; }

//-------------------------------------
void Mpris2Player::setVolume(double value) { m_player->setVolume(value); }

//-------------------------------------
QVariantMap Mpris2Player::metadata() {
  m_lastMeta = toXesam(m_player->songInfo());
  return m_lastMeta;
}

//-------------------------------------
double Mpris2Player::minimumRate() { return 1.0; }

//-------------------------------------
double Mpris2Player::maximumRate() { return 1.0; }

//-------------------------------------
double Mpris2Player::rate() { return 1.0; }

//-------------------------------------
void Mpris2Player::setRate(float value) { Q_UNUSED(value); }

//-------------------------------------
qlonglong Mpris2Player::position() {
  return m_player->songInfo().Position * SEC_TO_MICROSEC;
}

//-------------------------------------
bool Mpris2Player::canGoNext() {
  if (m_player->songInfo().isValid())
    return m_player->playerInfo().CanGoNext;
  return true;
}

//-------------------------------------
bool Mpris2Player::canGoPrevious() {
  if (m_player->songInfo().isValid())
    return m_player->playerInfo().CanGoPrevious;
  return true;
}

//-------------------------------------
bool Mpris2Player::canPlay() { return true; }

//-------------------------------------
bool Mpris2Player::canStop() { return false; }

//-------------------------------------
bool Mpris2Player::canPause() { return true; }

//-------------------------------------
bool Mpris2Player::canSeek() {
  if (m_player->songInfo().isValid())
    return m_player->playerInfo().CanGoPrevious;
  return true;
}

//-------------------------------------
bool Mpris2Player::canControl() { return true; }

//-------------------------------------
QMap<QString, QVariant> Mpris2Player::toXesam(const SongInfo &song) {
  QMap<QString, QVariant> map;
  if (song.isValid()) {
    QStringList artist;
    artist.append(song.ArtistName);
    map["xesam:url"] = song.SongTitle;
    map["xesam:artist"] = artist;
    map["xesam:album"] = song.AlbumTitle;
    map["xesam:title"] = song.SongTitle;
    if (song.Duration)
      map["mpris:length"] = (qlonglong)song.Duration * SEC_TO_MICROSEC;
    else
      map["mpris:length"] = 1;
    QString trackId =
        QString("/org/mpris/MediaPlayer2/Track/%1").arg(song.SongId);
    map["mpris:trackid"] = QVariant(QDBusObjectPath(trackId).path());
  } else {
    QStringList artist;
    artist.append("");
    map["xesam:url"] = "";
    map["xesam:artist"] = artist;
    map["xesam:album"] = "";
    map["xesam:title"] = "";
    map["mpris:length"] = 0;
    map["mpris:trackid"] =
        QVariant(QDBusObjectPath("/org/mpris/MediaPlayer2/NoTrack").path());
  }
  if (!song.LocalArtUrl.isEmpty())
    map["mpris:artUrl"] = "file://" + song.LocalArtUrl;
  else
    map["mpris:artUrl"] =
        "file://" + m_mainWindow->services()->currentService().IconFilePath;
  return map;
}
