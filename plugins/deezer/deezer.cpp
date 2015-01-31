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
bool DeezerPlugin::flashRequired()
{
    return true;
}

//---------------------------------------------------------
QUrl DeezerPlugin::url() const
{
    return QUrl("http://deezer.com");
}

//---------------------------------------------------------
void DeezerPlugin::play()
{
    runJavaScript("dzPlayer.control.play();");
}

//---------------------------------------------------------
void DeezerPlugin::pause()
{
    runJavaScript("dzPlayer.control.pause();");
}

//---------------------------------------------------------
void DeezerPlugin::stop()
{
    pause();
}

//---------------------------------------------------------
void DeezerPlugin::next()
{
    runJavaScript("dzPlayer.control.nextSong();");
}

//---------------------------------------------------------
void DeezerPlugin::previous()
{
    runJavaScript("dzPlayer.control.prevSong();");
}

//---------------------------------------------------------
void DeezerPlugin::seekToPosition(int position)
{
    // deezer use a normalised float value to represent the song duration
    // (0 = beginning, 1 = end)
    float percentage = position / float(currentSongInfo().duration);
    QString cmd = QString(
        "dzPlayer.control.seek(%1);").arg(QString::number(percentage));
    qDebug() << cmd;
    runJavaScript(cmd);
}

//---------------------------------------------------------
SongInfo DeezerPlugin::currentSongInfo()
{
    SongInfo retVal;

    retVal.songName = runJavaScript(
        "dzPlayer.getSongTitle();").toString();
    retVal.albumName = runJavaScript(
        "dzPlayer.getAlbumTitle();").toString();
    retVal.artistName = runJavaScript(
        "dzPlayer.getArtistName();").toString();
    retVal.duration = static_cast<qlonglong>(runJavaScript(
         "dzPlayer.getDuration();").toFloat() * 1000000);
    retVal.position = static_cast<qlonglong>(runJavaScript(
         "dzPlayer.getPosition();").toFloat() * 1000000);
    retVal.songId = runJavaScript(
        "dzPlayer.getSongId();").toString();


    QString coverId = runJavaScript("dzPlayer.getCover();").toString();
    retVal.artUrl = QString(
        "https://cdns-images.deezer.com/images/cover/%1/"
        "400x400.jpg").arg(coverId);

    return retVal;
}

//---------------------------------------------------------
PlaybackStatus DeezerPlugin::playbackStatus()
{
    bool loading = runJavaScript(
        "dzPlayer.loading;").toBool();
    bool playing = runJavaScript(
        "dzPlayer.playing;").toBool();
    bool paused = runJavaScript(
        "dzPlayer.paused;").toBool();
    if(playing)
        return Playing;
    else if(paused)
        return Paused;
    else if(loading)
        return Buffering;
    else
        return Stopped;
}

//---------------------------------------------------------
float DeezerPlugin::volume()
{
    return runJavaScript("dzPlayer.volume;").toFloat();
}

//---------------------------------------------------------
void DeezerPlugin::setVolume(float volume)
{
    QString cmd = QString(
        "dzPlayer.control.setVolume(%1);").arg(QString::number(volume));
    runJavaScript(cmd);
}

//---------------------------------------------------------
bool DeezerPlugin::canSeek()
{
    return runJavaScript("dzPlayer.control.canSeek()").toBool();
}

//---------------------------------------------------------
bool DeezerPlugin::canGoNext()
{
    return runJavaScript("dzPlayer.getNextSong() != null").toBool();
}

//---------------------------------------------------------
bool DeezerPlugin::canGoPrevious()
{
    return runJavaScript("dzPlayer.getPrevSong() != null").toBool();
}

//---------------------------------------------------------
bool DeezerPlugin::canFavorite()
{
    // fixme: check for login
    return true;
}

//---------------------------------------------------------
bool DeezerPlugin::isFavorite()
{
    return runJavaScript("$('.icon-love-circle').hasClass('active')").toBool();
}

//---------------------------------------------------------
void DeezerPlugin::addToFavorite(bool add)
{
    Q_UNUSED(add);
    runJavaScript("$('.icon-love-circle').get()[0].click()");
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( DeezerPlugin, DeezerPlugin )
#endif

