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

#include "rdio.h"

//---------------------------------------------------------
RdioPlugin::RdioPlugin()
{
    Q_INIT_RESOURCE(rdio);
}

//---------------------------------------------------------
bool RdioPlugin::flashRequired()
{
    // most services require flash, change it to false if you're
    // working on an html5 service.
    return false;
}


//---------------------------------------------------------
const PluginMetaData &RdioPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Rdio";
    meta.author = "Colin Duquesnoy";
    meta.author_website = "http://github.com/ColinDuquesnoy";
    meta.version = "1.0";
    meta.icon = QIcon(":/rdio/logo.png");
    meta.description =tr(
"<p><strong>Rdio</strong> is an online music service that offers ad-supported free streaming service and ad-free subscription "
"services in 85 countries.</p>"
"<p>It is available as a website and also has clients for the iPhone, iPod Touch & iPad, Android, "
"BlackBerry, and Windows Phone mobile devices, which can play streaming music or cache songs for offline playback. "
"There are also clients for the Roku and Sonos systems. The web-based service also offers a native desktop client application "
"for Mac OS X and Windows. Its library has content from the four major record labels, as well as the Merlin Network and the "
"aggregators IODA, INgrooves, The Orchard, CD Baby, IRIS Distribution, BFM Digital, Finetunes, and Catapult. Rdio also offers "
"social networking, allowing users to share playlists and follow others to see what music they listen to.</p>"
"<em>Source:"
"<a href=\"http://en.wikipedia.org/wiki/Rdio\">Rdio on Wikipedia</a>,"
"<a href=\"http://rdio.com\">Official website</a></em>"
"</p>");
    return meta;
}

//---------------------------------------------------------
QUrl RdioPlugin::url() const
{
    return QUrl("http://www.rdio.com");
}

//---------------------------------------------------------
void RdioPlugin::play()
{
    this->runJavaScript("R.Services.Player.play()");
}

//---------------------------------------------------------
void RdioPlugin::pause()
{
    this->runJavaScript("R.Services.Player.pause()");
}

//---------------------------------------------------------
void RdioPlugin::next()
{
    this->runJavaScript("R.Services.Player.next()");
}

//---------------------------------------------------------
void RdioPlugin::previous()
{
    this->runJavaScript("R.Services.Player.previous()");
}

//---------------------------------------------------------
void RdioPlugin::seekToPosition(int position)
{
    this->runJavaScript(QString("R.Services.Player.seek(%1)").arg(position / 1000000));
}

//---------------------------------------------------------
PlaybackStatus RdioPlugin::playbackStatus()
{
    PlaybackStatus status = Stopped;
    bool hasTrack = runJavaScript("R.Services.Player.model.get('playingTrack') != null").toBool();
    if(runJavaScript("R.Services.Player.isPlaying()").toBool())
        status = Playing;
    else if(hasTrack)
        status = Paused;
    return status;
}

//---------------------------------------------------------
SongInfo RdioPlugin::currentSongInfo()
{
    SongInfo retVal;
    if(playbackStatus() != Stopped)
    {
        retVal.songName = runJavaScript("R.Services.Player.model.get('playingTrack').attributes.name").toString();
        retVal.albumName = runJavaScript("R.Services.Player.model.get('playingTrack').attributes.album").toString();
        retVal.artistName = runJavaScript("R.Services.Player.model.get('playingTrack').attributes.artist").toString();
        retVal.artUrl = runJavaScript("R.Services.Player.model.get('playingTrack').attributes.icon").toString();
        retVal.songId = runJavaScript("R.Services.Player.model.get('playingTrack').attributes.key").toString();
        int duration = runJavaScript("R.Services.Player.model.get('playingTrack').attributes.duration").toInt();
        retVal.duration =  duration * 1000000;
        retVal.position = runJavaScript("R.Services.Player.position()").toInt() * 1000000;
    }
    return retVal;
}

//---------------------------------------------------------
float RdioPlugin::volume()
{
    return 1.f;
}

//---------------------------------------------------------
void RdioPlugin::setVolume(float volume)
{
    Q_UNUSED(volume);
}

//---------------------------------------------------------
bool RdioPlugin::canFavorite()
{
    return false;
}

//---------------------------------------------------------
bool RdioPlugin::isFavorite()
{
    return false;
}

//---------------------------------------------------------
void RdioPlugin::addToFavorite(bool add)
{
    Q_UNUSED(add);
}

//---------------------------------------------------------
bool RdioPlugin::canSeek()
{
    return true;
}

//---------------------------------------------------------
bool RdioPlugin::canGoNext()
{
    return playbackStatus() != Stopped ? true : false;
}

//---------------------------------------------------------
bool RdioPlugin::canGoPrevious()
{
    return playbackStatus() != Stopped ? true : false;
}
