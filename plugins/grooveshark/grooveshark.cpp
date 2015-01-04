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
#include "grooveshark.h"


//---------------------------------------------------------
QUrl GroovesharkPlugin::url()
{
    return QUrl("http://grooveshark.com");
}

//---------------------------------------------------------
void GroovesharkPlugin::play()
{
    this->runJavaScript("window.Grooveshark.play();");
}

//---------------------------------------------------------
void GroovesharkPlugin::pause()
{
    this->runJavaScript("window.Grooveshark.pause();");
}

//---------------------------------------------------------
void GroovesharkPlugin::stop()
{
    this->pause();
}

//---------------------------------------------------------
void GroovesharkPlugin::next()
{
    this->runJavaScript("window.Grooveshark.next();");
}

//---------------------------------------------------------
void GroovesharkPlugin::previous()
{
    this->runJavaScript("window.Grooveshark.previous();");
}

//---------------------------------------------------------
void GroovesharkPlugin::seekToPosition(int position)
{
    this->runJavaScript(
        QString("window.Grooveshark.seekToPosition(%1)").arg(
            QString::number(static_cast<int>(position/1000.f))));
}

//---------------------------------------------------------
SongInfo GroovesharkPlugin::currentSongInfo()
{
    SongInfo retVal;
    QVariantMap result = this->runJavaScript(
        "current_song = window.Grooveshark.getCurrentSongStatus()").toMap();
    QVariantMap songData = result["song"].toMap();
    retVal.songId = songData["songID"].toString();
    retVal.songName = songData["songName"].toString();
    retVal.albumName = songData["albumName"].toString();
    retVal.artistName = songData["artistName"].toString();
    retVal.artUrl = songData["artURL"].toString();
    // position from grooveshark are given in ms, we use µs.
    retVal.duration = songData["calculatedDuration"].toInt() * 1000;
    retVal.position = songData["position"].toInt() * 1000;
    QString statusString = result["status"].toString();
    retVal.playbackStatus = Stopped;
    if(statusString == "loading")
        retVal.playbackStatus = Loading;
    else if(statusString == "playing")
        retVal.playbackStatus = Playing;
    else if(statusString == "paused")
        retVal.playbackStatus = Paused;
    else if(statusString == "stopped")
        retVal.playbackStatus = Stopped;
    return retVal;
}

//---------------------------------------------------------
float GroovesharkPlugin::volume()
{
    float volume = this->runJavaScript("window.Grooveshark.getVolume())").toInt() / 100.0f;
    qDebug() << "Grooveshark volume" << volume;
    return volume;
}

//---------------------------------------------------------
void GroovesharkPlugin::setVolume(float volume)
{
    this->runJavaScript(
        QString("window.Grooveshark.setVolume(%1)").arg(
            QString::number(static_cast<int>(volume * 100))));
}
