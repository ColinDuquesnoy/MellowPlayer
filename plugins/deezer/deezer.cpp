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

#include "deezer.h"

//---------------------------------------------------------
DeezerPlugin::DeezerPlugin()
{
    Q_INIT_RESOURCE(deezer);
}

//---------------------------------------------------------
const PluginMetaData &DeezerPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Deezer";
    meta.author = "Colin Duquesnoy";
    meta.author_website = "Colin Duquesnoy";
    meta.version = "1.0";
    meta.icon = QIcon(":/deezer/deezer-logo.png");
    meta.description =tr(
"<p><strong>Deezer</strong> is a French web-based music streaming service."
"It allows users to listen to music on various devices online or offline. "
"It currently has 18 million licensed tracks, over 30,000 radio channels "
"and 22 million users (1.5 million subscribers)."
"</p>"
"<p>"
"<em>Source:"
"<a href=\"http://en.wikipedia.org/wiki/Deezer\">Grooveshark on Wikipedia</a>,"
"<a href=\"http://deezer.com\">Official website</a></em>"
"</p>");
    return meta;
}

//---------------------------------------------------------
QUrl DeezerPlugin::url() const
{
    return QUrl("http://deezer.com");
}

//---------------------------------------------------------
void DeezerPlugin::play()
{
    this->runJavaScript("dzPlayer.control.play();");
}

//---------------------------------------------------------
void DeezerPlugin::pause()
{
    this->runJavaScript("dzPlayer.control.pause();");
}

//---------------------------------------------------------
void DeezerPlugin::stop()
{
    this->pause();
}

//---------------------------------------------------------
void DeezerPlugin::next()
{
    this->runJavaScript("dzPlayer.control.nextSong();");
}

//---------------------------------------------------------
void DeezerPlugin::previous()
{
    this->runJavaScript("dzPlayer.control.prevSong();");
}

//---------------------------------------------------------
void DeezerPlugin::seekToPosition(int position)
{
    // not supported
    Q_UNUSED(position);
}

//---------------------------------------------------------
SongInfo DeezerPlugin::currentSongInfo()
{
    SongInfo retVal;

    retVal.songName = this->runJavaScript(
        "dzPlayer.getSongTitle();").toString();
    retVal.albumName = this->runJavaScript(
        "dzPlayer.getAlbumTitle();").toString();
    retVal.artistName = this->runJavaScript(
        "dzPlayer.getArtistName();").toString();
    retVal.duration = static_cast<qlonglong>(this->runJavaScript(
         "dzPlayer.getDuration();").toFloat() * 1000000);
    retVal.position = static_cast<qlonglong>(this->runJavaScript(
         "dzPlayer.getPosition();").toFloat() * 1000000);
    retVal.songId = this->runJavaScript(
        "dzPlayer.getSongId();").toString();
    bool loading = this->runJavaScript(
        "dzPlayer.loading;").toBool();
    bool playing = this->runJavaScript(
        "dzPlayer.playing;").toBool();
    bool paused = this->runJavaScript(
        "dzPlayer.paused;").toBool();
    if(loading)
        retVal.playbackStatus = Loading;
    else if(playing)
        retVal.playbackStatus = Playing;
    else if(paused)
        retVal.playbackStatus = Paused;
    else
        retVal.playbackStatus = Stopped;
    QString coverId = this->runJavaScript("dzPlayer.getCover();").toString();
    retVal.artUrl = QString(
        "https://cdns-images.deezer.com/images/cover/%1/"
        "400x400.jpg").arg(coverId);

    return retVal;
}

//---------------------------------------------------------
float DeezerPlugin::volume()
{
    // not supported
    return 1.f;
}

//---------------------------------------------------------
void DeezerPlugin::setVolume(float volume)
{
    // not supported
    Q_UNUSED(volume);
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( DeezerPlugin, DeezerPlugin )
#endif

