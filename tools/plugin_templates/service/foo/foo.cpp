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
#include <QtCore>
#include "foo.h"

//---------------------------------------------------------
QUrl FooPlugin::url()
{
    return QUrl("http://foo.com");
}

//---------------------------------------------------------
void FooPlugin::play()
{
    this->runJavaScript("window.Foo.play();");
}

//---------------------------------------------------------
void FooPlugin::pause()
{
    this->runJavaScript("window.Foo.pause();");
}

//---------------------------------------------------------
void FooPlugin::stop()
{
    this->pause();
}

//---------------------------------------------------------
void FooPlugin::next()
{
    this->runJavaScript("window.Foo.next();");
}

//---------------------------------------------------------
void FooPlugin::previous()
{
    this->runJavaScript("window.Foo.previous();");
}

//---------------------------------------------------------
void FooPlugin::seekToPosition(int position)
{
    this->runJavaScript(
        QString("window.Foo.seekToPosition(%1)").arg(
            QString::number(static_cast<int>(position/1000.f))));
}

//---------------------------------------------------------
SongInfo FooPlugin::currentSongInfo()
{
    SongInfo retVal;
    QVariantMap result = this->runJavaScript(
        "current_song = window.Foo.getCurrentSongStatus()").toMap();
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
float FooPlugin::volume()
{
    float volume = this->runJavaScript("window.Foo.getVolume())").toInt() / 100.0f;
    qDebug() << "Foo volume" << volume;
    return volume;
}

//---------------------------------------------------------
void FooPlugin::setVolume(float volume)
{
    this->runJavaScript(
        QString("window.Foo.setVolume(%1)").arg(
            QString::number(static_cast<int>(volume * 100))));
}
