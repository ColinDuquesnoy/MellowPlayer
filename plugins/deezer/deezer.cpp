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
"<p><strong>Deezer</strong> is a web-based music streaming service. "
"It allows users to listen to music content from record labels including EMI, "
"Sony, Universal Music Group, and Warner Music Group on various devices "
"online or offline. Created in Paris, France, Deezer currently has 35 million "
"licensed tracks in its library, over 30,000 radio channels, 16 million "
"monthly active users, and 5 million paid subscribers as of 6 November 2013."
"</p>"
"<p>"
"<em>Source:"
"<a href=\"http://en.wikipedia.org/wiki/Deezer\">Deezer on Wikipedia</a>,"
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
    // deezer use a normalised float value to represent the song duration
    // (0 = beginning, 1 = end)
    float percentage = position / float(this->currentSongInfo().duration);
    QString cmd = QString(
        "dzPlayer.control.seek(%1);").arg(QString::number(percentage));
    qDebug() << cmd;
    this->runJavaScript(cmd);
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

    bool playing = this->runJavaScript(
        "dzPlayer.playing;").toBool();
    bool paused = this->runJavaScript(
        "dzPlayer.paused;").toBool();
    if(playing)
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
    return this->runJavaScript("dzPlayer.volume;").toFloat();
}

//---------------------------------------------------------
void DeezerPlugin::setVolume(float volume)
{
    QString cmd = QString(
        "dzPlayer.control.setVolume(%1);").arg(QString::number(volume));
    this->runJavaScript(cmd);
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( DeezerPlugin, DeezerPlugin )
#endif

