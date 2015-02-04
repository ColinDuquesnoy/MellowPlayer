//---------------------------------------------------------
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
//---------------------------------------------------------

#include "mellowplayer/streamingservicesmanager.h"
#include "mellowplayer/player.h"
#include "mellowplayer/interfaces.h"
#include "mellowplayer/services.h"
#include "mellowplayer/urldownloader.h"


//---------------------------------------------------------
PlayerInterface::PlayerInterface(QObject *parent):
    QObject(parent),
    m_currentStatus(Stopped),
    m_currentPosition(0),
    m_canSeek(false),
    m_canPlay(false),
    m_canGoNext(false),
    m_canGoPrevious(false)
{
}

//---------------------------------------------------------
void PlayerInterface::playPause()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    SongInfo song = iService->currentSongInfo();
    if(playbackStatus() > Playing)
        iService->play();
    else
        iService->pause();
}

//---------------------------------------------------------
void PlayerInterface::stop()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->stop();
}

//---------------------------------------------------------
void PlayerInterface::next()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->next();
}

//---------------------------------------------------------
void PlayerInterface::previous()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->previous();
}

//---------------------------------------------------------
void PlayerInterface::seekToPosition(int position)
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->seekToPosition(position);
}

//---------------------------------------------------------
bool PlayerInterface::canPlay()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return false;
    return true;
}

//---------------------------------------------------------
bool PlayerInterface::canSeek()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return false;
    return iService->canSeek();
}

//---------------------------------------------------------
bool PlayerInterface::canGoNext()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return true;
    return iService->canGoNext();
}

//---------------------------------------------------------
bool PlayerInterface::canGoPrevious()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return true;
    return iService->canGoPrevious();
}

//---------------------------------------------------------
SongInfo PlayerInterface::currentSong()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService)
        return SongInfo(); // invalid song
    return iService->currentSongInfo();
}

//---------------------------------------------------------
SongInfo PlayerInterface::update()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService)
        return SongInfo();  // invalid song
    SongInfo song = iService->currentSongInfo();
    checkPlaybackStatusChange(song);
    checkSongChange(song);
    checkForPositionChange(song);
    checkForControlCaps();
    return song;
}

//---------------------------------------------------------
float PlayerInterface::volume()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return 0.0f;
    return iService->volume();
}

//---------------------------------------------------------
void PlayerInterface::setVolume(float value)
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(iService && iService->currentSongInfo().isValid())
        iService->setVolume(value);
}

//---------------------------------------------------------
PlaybackStatus PlayerInterface::playbackStatus() const
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    PlaybackStatus status = Stopped;
    if(iService)
         status = iService->playbackStatus();
    return status;
}

//---------------------------------------------------------
bool PlayerInterface::canFavorite()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(iService)
         return iService->canFavorite();
    return false;
}

//---------------------------------------------------------
bool PlayerInterface::isFavorite()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(iService)
         return iService->isFavorite();
    return false;
}

//---------------------------------------------------------
void PlayerInterface::addToFavorites()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(iService)
         iService->addToFavorite(!iService->isFavorite());

}

//---------------------------------------------------------
const QString& PlayerInterface::currentArt() const
{
    return m_currentArt;
}

//---------------------------------------------------------
void PlayerInterface::onArtReady(const QString &filePath)
{
    this->m_currentArt = filePath;
    emit artReady(filePath);
}

//---------------------------------------------------------
void PlayerInterface::checkPlaybackStatusChange(SongInfo &song)
{
    PlaybackStatus status = Stopped;
    if(song.isValid())
        status = playbackStatus();
    if(status != m_currentStatus)
    {
        qDebug() << "Playback status changed: "
                 << playbackStatusToString((status));
        m_currentStatus = status;
        emit playbackStatusChanged(status);
    }
}

//---------------------------------------------------------
void PlayerInterface::checkSongChange(SongInfo &song)
{
    if(song.songName != m_currentSong.songName)
    {
        m_currentArt = "";
        qDebug() << "Song changed: " << song.songName;
        emit songChanged(song);
        m_currentSong = song;

        if(playbackStatus() == Playing && song.isValid())
        {
            m_startedSong = song;
            emit songStarted(song);
        }
        else
            m_startedSong = SongInfo(); // invalid song

        if(song.isValid())
        {
            downloadSongArt(song.artUrl);
        }
    }
    else if(!m_startedSong.isValid() && playbackStatus() == Playing)
    {
        // sometimes (depends on the player) a new song is active but not playing,
        // we only emit song started when a song is active and the player is playing.
        m_startedSong = song;
        emit songStarted(song);
    }
}

//---------------------------------------------------------
void PlayerInterface::checkForPositionChange(SongInfo &song)
{
    if(m_currentPosition != song.position)
    {
        emit positionChanged(song.position);
        m_currentPosition = song.position;
    }
}

//---------------------------------------------------------
void PlayerInterface::checkForControlCaps()
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(iService)
    {
        if(canGoNext() != m_canGoNext ||
           canGoPrevious() != m_canGoPrevious ||
           canPlay() != m_canPlay ||
           canSeek() != m_canSeek)
        {
            m_canGoNext = canGoNext();
            m_canGoPrevious = canGoPrevious();
            m_canPlay = canPlay();
            m_canSeek = canSeek();

            emit controlCapsChanged();
        }
    }
}

//---------------------------------------------------------
void PlayerInterface::downloadSongArt(const QString& url)
{
    UrlDownloader* downloader = new UrlDownloader(this);
    QString dest = QDir::temp().path() +
                   QString(QDir::separator()) +
                   currentSong().songId +
                   QFileInfo(url).fileName();
    connect(downloader, SIGNAL(finished(const QString&)),
            this, SLOT(onArtReady(const QString&)));

    downloader->download(url, dest);
}


