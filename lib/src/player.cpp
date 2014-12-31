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

#include "mellowplayer/cloudservicesmanager.h"
#include "mellowplayer/player.h"
#include "mellowplayer/plugins.h"
#include "mellowplayer/services.h"


//---------------------------------------------------------
PlayerInterface::PlayerInterface(QObject *parent):
    QObject(parent)
{

}

//---------------------------------------------------------
void PlayerInterface::playPause()
{
    ICloudMusicService* iService =
            Services::cloudServices()->currentService();
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
    ICloudMusicService* iService =
            Services::cloudServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->stop();
}

//---------------------------------------------------------
void PlayerInterface::next()
{
    ICloudMusicService* iService =
            Services::cloudServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->next();
}

//---------------------------------------------------------
void PlayerInterface::previous()
{
    ICloudMusicService* iService =
            Services::cloudServices()->currentService();
    if(!iService || !iService->currentSongInfo().isValid())
        return;
    iService->previous();
}

//---------------------------------------------------------
SongInfo PlayerInterface::getCurrentSong()
{
    ICloudMusicService* iService =
            Services::cloudServices()->currentService();
    if(!iService)
        return SongInfo(); // invalid song
    return iService->currentSongInfo();
}

//---------------------------------------------------------
SongInfo PlayerInterface::update()
{
    ICloudMusicService* iService =
            Services::cloudServices()->currentService();
    if(!iService)
        return SongInfo();  // invalid song
    SongInfo song = iService->currentSongInfo();
    this->checkPlaybackStatusChange(song);
    this->checkSongChange(song);
    return song;
}

//---------------------------------------------------------
void PlayerInterface::checkPlaybackStatusChange(SongInfo &song)
{
    PlaybackStatus status = Stopped;
    if(song.isValid())
        status = song.playbackStatus;
    if(status != this->currentStatus)
    {
        this->currentStatus = status;
        emit playbackStatusChanged(status);
    }
}

//---------------------------------------------------------
void PlayerInterface::checkSongChange(SongInfo &song)
{
    if(song.songName != this->currentSong.songName)
    {
        this->currentSong = song;
        emit songChanged(song);
        // todo implement song art download when the FileDownloader is ready.
//        if(song.isValid())
//            this->downloadSongArt(song.artUrl);
    }

}






