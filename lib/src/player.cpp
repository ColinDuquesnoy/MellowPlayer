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
    currentStatus(Stopped),
    currentPosition(0)
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
    if(this->playbackStatus() > Playing)
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
    this->checkPlaybackStatusChange(song);
    this->checkSongChange(song);
    this->checkForPositionChange(song);
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

PlaybackStatus PlayerInterface::playbackStatus() const
{
    IStreamingService* iService =
            Services::streamingServices()->currentService();
    if(iService)
        return iService->playbackStatus();
    return Stopped;
}

//---------------------------------------------------------
void PlayerInterface::onArtReady(const QString &filePath)
{
    emit this->artReady(filePath);
}

//---------------------------------------------------------
void PlayerInterface::checkPlaybackStatusChange(SongInfo &song)
{
    PlaybackStatus status = Stopped;
    if(song.isValid())
        status = playbackStatus();
    if(status != this->currentStatus)
    {
        qDebug() << "Playback status changed: "
                 << playbackStatusToString((status));
        this->currentStatus = status;
        emit playbackStatusChanged(status);
    }
}

//---------------------------------------------------------
void PlayerInterface::checkSongChange(SongInfo &song)
{
    if(song.songName != this->_currentSong.songName)
    {
        qDebug() << "Song changed: " << song.songName;
        emit songChanged(song);
        this->_currentSong = song;

        if(this->playbackStatus() == Playing && song.isValid())
        {
            this->_startedSong = song;
            emit songStarted(song);
        }
        else
            this->_startedSong = SongInfo(); // invalid song

        if(song.isValid())
            this->downloadSongArt(song.artUrl);
    }
    else if(!this->_startedSong.isValid() && this->playbackStatus() == Playing)
    {
        // sometimes (depends on the player) a new song is active but not playing,
        // we only emit song started when a song is active and the player is playing.
        this->_startedSong = song;
        emit songStarted(song);
    }
}

//---------------------------------------------------------
void PlayerInterface::checkForPositionChange(SongInfo &song)
{
    if(this->currentPosition != song.position)
    {
        emit positionChanged(song.position);
        this->currentPosition = song.position;
    }
}

//---------------------------------------------------------
void PlayerInterface::downloadSongArt(const QString& url)
{
    UrlDownloader* downloader = new UrlDownloader(this);
    QString dest = QDir::temp().path() +
                   QString(QDir::separator()) +
                   this->currentSong().songId +
                   QFileInfo(url).fileName();
    connect(downloader, SIGNAL(finished(const QString&)),
            this, SLOT(onArtReady(const QString&)));

    downloader->download(url, dest);
}


