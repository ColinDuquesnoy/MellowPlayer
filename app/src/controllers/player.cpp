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
#include "controllers/player.h"
#include "controllers/services.h"
#include "utils/icons.h"
#include "views/mainwindow.h"
#include "ui_mainwindow.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
PlayerController::PlayerController(MainWindow *parent)
    : BaseController("player", parent), m_pollingTimer(new QTimer(this)),
      m_webView(parent->ui()->webView), m_nam(new QNetworkAccessManager(this)) {
  m_pollingTimer->setInterval(100);
  connect(m_pollingTimer, &QTimer::timeout, this, &PlayerController::update);
  connect(m_mainWindow->ui()->actionPlayPause, &QAction::triggered, this,
          &PlayerController::playPause);
  connect(m_mainWindow->ui()->actionNext, &QAction::triggered, this,
          &PlayerController::next);
  connect(m_mainWindow->ui()->actionPrevious, &QAction::triggered, this,
          &PlayerController::previous);
  connect(m_mainWindow->ui()->actionAdd_to_favorites, &QAction::toggled, this,
          &PlayerController::onFavoriteChanged);
  connect(m_nam, &QNetworkAccessManager::finished, this,
          &PlayerController::onDownloadFinished);
  m_mainWindow->ui()->actionAdd_to_favorites->setCheckable(true);
  m_mainWindow->ui()->actionAdd_to_favorites->setChecked(false);
  m_mainWindow->ui()->actionAdd_to_favorites->setVisible(false);
}

//--------------------------------------
void PlayerController::startPolling() {
  m_playerInfo = PlayerInfo();
  m_songInfo = SongInfo();
  m_pollingTimer->start();
}

//--------------------------------------
void PlayerController::stopPolling() { m_pollingTimer->stop(); }

//--------------------------------------
const PlayerInfo &PlayerController::playerInfo() const { return m_playerInfo; }

//--------------------------------------
const SongInfo &PlayerController::songInfo() const { return m_songInfo; }

//--------------------------------------
void PlayerController::update() {
  QString script("function update(){\n"
                 "    return {'playerInfo': updatePlayerInfo(),\n"
                 "            'songInfo': updateSongInfo()};\n"
                 "}\n"
                 "update();");

  m_webView->page()->runJavaScript(script, [this](const QVariant &result) {
    this->onUpdateFinished(result);
  });
}

//--------------------------------------
void PlayerController::playPause() {
  if (m_playerInfo.Status == PlayerStatus::Playing ||
      m_playerInfo.Status == PlayerStatus::Buffering)
    pause();
  else
    play();
}

//--------------------------------------
void PlayerController::play() { m_webView->page()->runJavaScript("play()"); }

//--------------------------------------
void PlayerController::pause() { m_webView->page()->runJavaScript("pause()"); }

//--------------------------------------
void PlayerController::next() { m_webView->page()->runJavaScript("goNext()"); }

//--------------------------------------
void PlayerController::previous() {
  m_webView->page()->runJavaScript("goPrevious()");
}

//--------------------------------------
void PlayerController::addToFavorites() {
  m_webView->page()->runJavaScript("addToFavorites()");
}

//--------------------------------------
void PlayerController::removeFromFavorites() {
  m_webView->page()->runJavaScript("removeFromFavorites()");
}

//--------------------------------------
void PlayerController::setVolume(float value) {
  m_webView->page()->runJavaScript(QString("setVolume(%1)").arg(value));
}

//--------------------------------------
void PlayerController::seekToPosition(qlonglong position) {
  m_webView->page()->runJavaScript(QString("seekToPosition(%1)").arg(position));
}

//--------------------------------------
void PlayerController::onFavoriteChanged(bool favorite) {
  if (favorite) {
    addToFavorites();
  } else {
    removeFromFavorites();
  }
}

//--------------------------------------
void PlayerController::onUpdateFinished(const QVariant &result) {
  if (m_mainWindow == nullptr)
    return;
  QVariantMap resultMap = result.toMap();
  QVariantMap songInfoData = resultMap.value("songInfo").toMap();
  QVariantMap playerInfoData = resultMap.value("playerInfo").toMap();
  StreamingServicesController *services = m_mainWindow->services();
  if (services == nullptr)
    return;
  StreamingServicePlugin service = services->currentService();
  SongInfo songInfo = songFromQVariantMap(songInfoData);
  PlayerInfo playerInfo = playerInfoFromQVariantMap(playerInfoData);

  SongInfo prevSong = m_songInfo;
  PlayerInfo prevPlayerInfo = m_playerInfo;

  if (m_songInfo == songInfo && m_songInfo.Duration > 1)
    // prevent duration from being reset during buffering on mixcloud.
    songInfo.Duration = m_songInfo.Duration;
  // keep local art url
  songInfo.LocalArtUrl = m_songInfo.LocalArtUrl;
  m_songInfo = songInfo;
  m_playerInfo = playerInfo;

  // Detect and signal changes in the song properties.
  if (prevSong.Position != m_songInfo.Position)
    emit songPositionChanged(m_songInfo.Position);
  if (prevSong.Duration != m_songInfo.Duration)
    emit songDurationAvailable(m_songInfo);
  if (prevSong != m_songInfo) {
    m_songInfo.LocalArtUrl = "";
    downloadArtUrl(m_songInfo);
    emit songChanged(m_songInfo);
  }
  // Detect and signal changes in the web player info
  if (prevPlayerInfo.Status != m_playerInfo.Status)
    emit playerStatusChanged(m_playerInfo.Status);
  if (m_playerInfo.Volume != prevPlayerInfo.Volume)
    emit volumeChanged(m_playerInfo.Volume);
  if (m_playerInfo != prevPlayerInfo) // only caps are checked here
    emit playerCapsChanged(m_playerInfo);

  // Update window state
  if (songInfo.isValid()) {
    m_mainWindow->setInfoLabelText(songInfo.toPrettyString());
    m_mainWindow->ui()->actionPlayPause->setEnabled(true);
    m_mainWindow->ui()->actionNext->setEnabled(playerInfo.CanGoNext);
    m_mainWindow->ui()->actionPrevious->setEnabled(playerInfo.CanGoPrevious);
    m_mainWindow->ui()->actionAdd_to_favorites->setEnabled(
        playerInfo.CanAddToFavorites);
    m_mainWindow->ui()->actionAdd_to_favorites->setVisible(
        playerInfo.CanAddToFavorites);
    m_mainWindow->ui()->actionAdd_to_favorites->blockSignals(true);
    m_mainWindow->ui()->actionAdd_to_favorites->setChecked(songInfo.Favorite);
    m_mainWindow->ui()->actionAdd_to_favorites->blockSignals(false);
    PlayerStatus playbackStatus = playerInfo.Status;
    bool playing = playbackStatus == PlayerStatus::Playing ||
                   playbackStatus == PlayerStatus::Buffering;
    m_mainWindow->ui()->actionPlayPause->setIcon(playing ? Icons::pause()
                                                         : Icons::play());
  } else {
    m_mainWindow->setWindowTitle(service.Name);
    m_mainWindow->setInfoLabelText(service.Name);
    m_mainWindow->ui()->actionPlayPause->setEnabled(false);
    m_mainWindow->ui()->actionNext->setEnabled(false);
    m_mainWindow->ui()->actionPrevious->setEnabled(false);
    m_mainWindow->ui()->actionAdd_to_favorites->setEnabled(false);
    m_mainWindow->ui()->actionAdd_to_favorites->setVisible(false);
  }

  // Store results for next update
  m_playerInfo = playerInfo;
}

//--------------------------------------
QFileInfo getLocalArtUrl(const QString &songId, const QString &sv) {
  QString cacheDir =
      QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0];
  QFileInfo dir = QFileInfo(cacheDir, "Covers");
  QString dirPath = dir.absoluteFilePath();
  if (!dir.exists()) {
    QDir(cacheDir).mkdir("Covers");
  }
  QFileInfo localArtUrl = QFileInfo(dirPath, sv + "-" + songId);
  return localArtUrl;
}

//--------------------------------------
void PlayerController::onDownloadFinished(QNetworkReply *reply) {
  QString sv = m_mainWindow->services()->currentService().Name;
  m_songInfo.LocalArtUrl =
      getLocalArtUrl(m_songInfo.SongId, sv).absoluteFilePath();
  QFile file(m_songInfo.LocalArtUrl);
  if (file.open(QIODevice::WriteOnly)) {
    file.write(reply->readAll());
    file.close();
  }
  emit songArtReady(m_songInfo.LocalArtUrl);
}

//--------------------------------------
void PlayerController::downloadArtUrl(const SongInfo &songInfo) {
  qDebug() << songInfo.ArtUrl;
  QString sv = m_mainWindow->services()->currentService().Name;
  QFileInfo localArtUrl = getLocalArtUrl(songInfo.SongId, sv);
  if (localArtUrl.exists()) {
    m_songInfo.LocalArtUrl = localArtUrl.absoluteFilePath();
    emit songArtReady(m_songInfo.LocalArtUrl);
  } else {
    qDebug() << "Art url:" << songInfo.ArtUrl;
    m_nam->get(QNetworkRequest(songInfo.ArtUrl));
  }
}
