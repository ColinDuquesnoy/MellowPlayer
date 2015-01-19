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
    IStreamingServiceIntegration* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    SongInfo song = iService->currentSongInfo();
    if(song.playbackStatus > Playing)
        iService->play();
    else
        iService->pause();
}

//---------------------------------------------------------
void PlayerInterface::stop()
{
    IStreamingServiceIntegration* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->stop();
}

//---------------------------------------------------------
void PlayerInterface::next()
{
    IStreamingServiceIntegration* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->next();
}

//---------------------------------------------------------
void PlayerInterface::previous()
{
    IStreamingServiceIntegration* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->previous();
}

//---------------------------------------------------------
void PlayerInterface::seekToPosition(int position)
{
    IStreamingServiceIntegration* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->seekToPosition(position);
}

//---------------------------------------------------------
SongInfo PlayerInterface::currentSong()
{
    IStreamingServiceIntegration* iService =
            Services::streamingServices()->currentService();
    if(!iService)
        return SongInfo(); // invalid song
    return iService->currentSongInfo();
}

//---------------------------------------------------------
SongInfo PlayerInterface::update()
{
    IStreamingServiceIntegration* iService =
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
    IStreamingServiceIntegration* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return iService->volume();
    return 0.0f;
}

//---------------------------------------------------------
void PlayerInterface::setVolume(float value)
{
    IStreamingServiceIntegration* iService =
            Services::streamingServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        iService->setVolume(value);
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
        status = song.playbackStatus;
    if(status != this->currentStatus)
    {
        qDebug() << "Playback status changed: "
                 << playbackStatusToStringTr((status));
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
        this->_currentSong = song;
        emit songChanged(song);
        if(song.isValid())
            this->downloadSongArt(song.artUrl);
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
                   QFileInfo(url).fileName();
    connect(downloader, SIGNAL(finished(const QString&)),
            this, SLOT(onArtReady(const QString&)));

    downloader->download(url, dest);
}


