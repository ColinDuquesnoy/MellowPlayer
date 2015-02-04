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
GroovesharkPlugin::GroovesharkPlugin()
{
    Q_INIT_RESOURCE(grooveshark);  // grooveshark.qrc
}

//---------------------------------------------------------
const PluginMetaData &GroovesharkPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Grooveshark";
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
bool GroovesharkPlugin::flashRequired()
{
    return true;
}

//---------------------------------------------------------
QUrl GroovesharkPlugin::url() const
{
    return QUrl("http://grooveshark.com");
}

//---------------------------------------------------------
void GroovesharkPlugin::play()
{
    runJavaScript("window.Grooveshark.play();");
}

//---------------------------------------------------------
void GroovesharkPlugin::pause()
{
    runJavaScript("window.Grooveshark.pause();");
}

//---------------------------------------------------------
void GroovesharkPlugin::stop()
{
    pause();
}

//---------------------------------------------------------
void GroovesharkPlugin::next()
{
    runJavaScript("window.Grooveshark.next();");
}

//---------------------------------------------------------
void GroovesharkPlugin::previous()
{
    runJavaScript("window.Grooveshark.previous();");
}

//---------------------------------------------------------
void GroovesharkPlugin::seekToPosition(int position)
{
    runJavaScript(
        QString("window.Grooveshark.seekToPosition(%1)").arg(
            QString::number(static_cast<int>(position/1000.f))));
}

//---------------------------------------------------------
SongInfo GroovesharkPlugin::currentSongInfo()
{
    SongInfo retVal;
    QVariantMap result = runJavaScript(
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

    return retVal;
}

//---------------------------------------------------------
PlaybackStatus GroovesharkPlugin::playbackStatus()
{
    QVariantMap result = runJavaScript(
        "current_song = window.Grooveshark.getCurrentSongStatus()").toMap();
    QString statusString = result["status"].toString();
    if(statusString == "playing")
        return Playing;
    else if(statusString == "paused")
        return Paused;
    else if(statusString == "loading" || currentSongInfo().isValid())
        return Buffering;
    else
        return Stopped;
}

//---------------------------------------------------------
float GroovesharkPlugin::volume()
{
    float volume = runJavaScript(
        "window.Grooveshark.getVolume())").toInt() / 100.0f;
    qDebug() << "Grooveshark volume" << volume;
    return volume;
}

//---------------------------------------------------------
void GroovesharkPlugin::setVolume(float volume)
{
    runJavaScript(
        QString("window.Grooveshark.setVolume(%1)").arg(
                    QString::number(static_cast<int>(volume * 100))));
}

//---------------------------------------------------------
bool GroovesharkPlugin::canSeek()
{
    // seems like there is no way to know if the user joined a brodcast, this
    // is the only condition where canSeek should return false.
    return true;
}

//---------------------------------------------------------
bool GroovesharkPlugin::canGoNext()
{
    return runJavaScript("Grooveshark.getNextSong() != null").toBool();
}

//---------------------------------------------------------
bool GroovesharkPlugin::canGoPrevious()
{
    return runJavaScript("Grooveshark.getPreviousSong() != null").toBool();
}

//---------------------------------------------------------
bool GroovesharkPlugin::canFavorite()
{
    return true;
}

//---------------------------------------------------------
bool GroovesharkPlugin::isFavorite()
{
    return runJavaScript("$('#np-fav').hasClass('active')").toBool();
}

//---------------------------------------------------------
void GroovesharkPlugin::addToFavorite(bool add)
{
    Q_UNUSED(add);
    runJavaScript("$('#np-fav').get()[0].click()");
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( GroovesharkPlugin, GroovesharkPlugin )
#endif
