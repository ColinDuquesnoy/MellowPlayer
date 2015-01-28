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

#include "groovesharkmobile.h"
#include <QWebView>

//---------------------------------------------------------
GroovesharkmobilePlugin::GroovesharkmobilePlugin()
{
    Q_INIT_RESOURCE(groovesharkmobile);
}

//---------------------------------------------------------
const PluginMetaData &GroovesharkmobilePlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Grooveshark Mobile";
    meta.author = "Colin Duquesnoy";
    meta.author_website = "https://github.com/ColinDuquesnoy";
    meta.version = "1.0";
    meta.icon = QIcon(":/grooveshark/logo.png");
    meta.description =tr(
"<p><strong>Grooveshark</strong> is an international online music search "
"engine, music streaming service and music recommendation web software "
"application, allowing users to search for, stream, and upload music that can "
"be played immediately or added to a playlist. An optional paid subscription "
"adds additional functionality and removes advertisements."
"</p><p>"
"<em>Source:"
"<a href=\"http://en.wikipedia.org/wiki/Grooveshark\">Grooveshark on Wikipedia</a>,"
"<a href=\"http://grooveshark.com\">Official website</a></em>"
"</p>");
    return meta;
}

//---------------------------------------------------------
QUrl GroovesharkmobilePlugin::url() const
{
    return QUrl("http://html5.grooveshark.com/");
}

//---------------------------------------------------------
void GroovesharkmobilePlugin::play()
{
    this->runJavaScript("GS.audio.pauseResume();");
}

//---------------------------------------------------------
void GroovesharkmobilePlugin::pause()
{
    this->runJavaScript("GS.audio.pauseResume();");
}

//---------------------------------------------------------
void GroovesharkmobilePlugin::stop()
{
    this->pause();
}

//---------------------------------------------------------
void GroovesharkmobilePlugin::next()
{
    this->runJavaScript("GS.audio.playNext();");
}

//---------------------------------------------------------
void GroovesharkmobilePlugin::previous()
{
    this->runJavaScript("GS.models.queue.prev() && GS.audio.playNow();");
}

//---------------------------------------------------------
void GroovesharkmobilePlugin::seekToPosition(int position)
{
    Q_UNUSED(position); // player cannot seek
}

//---------------------------------------------------------
PlaybackStatus GroovesharkmobilePlugin::playbackStatus()
{
    if(runJavaScript("GS.audio.model == null").toBool())
        return Stopped;
    if(runJavaScript("GS.audio.audio.paused").toBool())
        return Paused;
    return isPageLoaded() ? Playing : Stopped;
}

//---------------------------------------------------------
SongInfo GroovesharkmobilePlugin::currentSongInfo()
{
    SongInfo retVal;
    if(playbackStatus() != Stopped)
    {
        bool subscribedToBroadCast = runJavaScript(
            "GS.audio.isSubscribedToBroadcast()").toBool();
        QString getSong;
        if(subscribedToBroadCast)
            getSong = "var song = GS.audio.model.get('activeSong');\n";
        else
            getSong = "var song = GS.audio.model;\n";
        retVal.songName = runJavaScript(getSong +
                                        "song.get('Name')").toString();
        if(!retVal.isValid())
            retVal.songName = runJavaScript(getSong +
                                            "song.get('SongName')").toString();
        if(retVal.isValid())
        {
            retVal.albumName = runJavaScript(
                getSong + "song.get('AlbumName')").toString();
            retVal.artistName = runJavaScript(
                getSong + "song.get('ArtistName')").toString();
            retVal.artUrl = runJavaScript(
                getSong + "song.get('coverURL500')").toString();
            retVal.songId = runJavaScript(
                getSong + "song.get('SongID')").toString();

            QVariantList values = runJavaScript(
                "GS.audio.getProgress()").toList();
            retVal.position = values[0].toFloat() * 1000000;
            retVal.duration = values[1].toFloat() * 1000000;

        }
    }
    return retVal;
}

//---------------------------------------------------------
float GroovesharkmobilePlugin::volume()
{
    return 1.f;
}

//---------------------------------------------------------
void GroovesharkmobilePlugin::setVolume(float volume)
{
    Q_UNUSED(volume);
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( GroovesharkmobilePlugin, GroovesharkmobilePlugin )
#endif
