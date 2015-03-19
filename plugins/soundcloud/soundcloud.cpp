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

#include "soundcloud.h"

//---------------------------------------------------------
SoundcloudPlugin::SoundcloudPlugin()
{
    Q_INIT_RESOURCE(soundcloud);
    id = 0;
}

//---------------------------------------------------------
const PluginMetaData &SoundcloudPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Soundcloud";
    meta.author = "Colin Duquesnoy";
    meta.author_website = "https://github.com/ColinDuquesnoy";
    meta.version = "1.0";
    meta.icon = QIcon(":/soundcloud/logo-black.png");
    meta.description =tr(
"<p><strong>SoundCloud</strong> is a Swedish online audio distribution platform based in Berlin, Germany, "
"that enables its users to upload, record, promote, and share their originally-created sounds.</p> "
"<p>According to the company’s data, in December 2014, the service attracts more than "
"175 million unique monthly listeners, while content creators upload about 12 hours worth of audio "
"every minute.</p><p>Founders Alexander Ljung and Eric Wahlforss are the chief executive officer (CEO) and "
"chief technical officer (CTO), respectively.</p>");
    return meta;
}

//---------------------------------------------------------
bool SoundcloudPlugin::flashRequired()
{
    return true;
}

//---------------------------------------------------------
QUrl SoundcloudPlugin::url() const
{
    return QUrl("http://soundcloud.com");
}

//---------------------------------------------------------
void SoundcloudPlugin::play()
{
#ifdef Q_OS_WIN32
    runJavaScript("$('.playControl').click()");
#else
    this->runJavaScript("$('.playControl').get()[0].click()");
#endif
}

//---------------------------------------------------------
void SoundcloudPlugin::pause()
{
    this->play();
}

//---------------------------------------------------------
void SoundcloudPlugin::stop()
{
    pause();
}

//---------------------------------------------------------
void SoundcloudPlugin::next()
{
#ifdef Q_OS_WIN32
    runJavaScript("$('.skipControl__next').click()");
#else
    runJavaScript("$('.skipControl__next').get()[0].click()");
#endif
}

//---------------------------------------------------------
void SoundcloudPlugin::previous()
{
#ifdef Q_OS_WIN32
    runJavaScript("$('.skipControl__previous').click()");
#else
    runJavaScript("$('.skipControl__previous').get()[0].click()");
#endif
}

//---------------------------------------------------------
void SoundcloudPlugin::seekToPosition(int position)
{
    Q_UNUSED(position);
}

//---------------------------------------------------------
PlaybackStatus SoundcloudPlugin::playbackStatus()
{
    QString className = runJavaScript("$('.playControl').attr('class')").toString();

    if(className.contains("disabled"))
        return Stopped;
    else if(className.contains("playing"))
        return Playing;
    else
        return Paused;
    return Stopped;
}

//---------------------------------------------------------
SongInfo SoundcloudPlugin::currentSongInfo()
{
    SongInfo retVal;
    retVal.songName = runJavaScript("$('.playbackTitle__link').text()").toString();
    retVal.position = runJavaScript("$('.playbackTitle__progress').attr('aria-valuenow')").toFloat() * 1000;
    retVal.duration = runJavaScript("$('.playbackTitle__progress').attr('aria-valuemax')").toFloat() * 1000;
    retVal.songId = QString::number(qt_hash(retVal.songName));
    return retVal;
}

//---------------------------------------------------------
float SoundcloudPlugin::volume()
{
    return 1.f;
}

//---------------------------------------------------------
void SoundcloudPlugin::setVolume(float volume)
{
    Q_UNUSED(volume);
}

//---------------------------------------------------------
bool SoundcloudPlugin::canFavorite()
{
    return false;
}

//---------------------------------------------------------
bool SoundcloudPlugin::isFavorite()
{
    return false;
}

//---------------------------------------------------------
void SoundcloudPlugin::addToFavorite(bool add)
{
    Q_UNUSED(add);
}

//---------------------------------------------------------
bool SoundcloudPlugin::canSeek()
{
    return true; // cannot seek but set it to true to show progress
}

//---------------------------------------------------------
bool SoundcloudPlugin::canGoNext()
{
    return true;
}

//---------------------------------------------------------
bool SoundcloudPlugin::canGoPrevious()
{
    return !runJavaScript("$('.skipControl__previous').attr('class')").toString(
        ).contains("disabled");
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( SoundcloudPlugin, SoundcloudPlugin )
#endif
