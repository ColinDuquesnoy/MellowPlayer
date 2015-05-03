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
    meta.version = "1.1";
    meta.icon = QIcon(":/soundcloud/logo.png");
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
    retVal.songName = runJavaScript("$('.playbackSoundBadge__title').text()").toString();
    QString progress = runJavaScript("$('.playbackTimeline__timePassed').text()").toString();
    retVal.position = stringToTime(progress);
    QString duration = runJavaScript("$('.playbackTimeline__duration').text()").toString();
    retVal.duration = stringToTime(duration);
    QString url = runJavaScript("$('.playbackSoundBadge').children(0).children(0).children(0).css('background-image')").toString();
    retVal.artUrl = url.left(url.length() - 1).replace("url(", "").replace("t50x50", "t120x120");
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

qlonglong SoundcloudPlugin::stringToTime(const QString &string)
{
    QString format;
    switch (string.length()) {
    case 4:
        format = "m:ss";
        break;
    case 5:
        format = "mm:ss";
        break;
    case 7:
        format = "h:mm:ss";
        break;
    case 8:
        format = "hh:mm:ss";
        break;
    default:
        break;
    }
    QTime time = QTime::fromString(string, format);
    int seconds = QTime(0, 0, 0).secsTo(time);
    return seconds * 1000000;
}
