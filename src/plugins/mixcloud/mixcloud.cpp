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

#include <QWebView>
#include "mixcloud.h"

//---------------------------------------------------------
MixcloudPlugin::MixcloudPlugin()
{
    Q_INIT_RESOURCE(mixcloud);
}

//---------------------------------------------------------
const PluginMetaData &MixcloudPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Mixcloud";
    meta.author = "Colin Duquesnoy";
    meta.author_website = "https://github.com/ColinDuquesnoy";
    meta.version = "1.2";
    meta.icon = QIcon(":/mixcloud/logo.png");
    meta.description =tr(
"Mixcloud is an online music streaming service that allows for the listening "
"and distribution of radio shows, DJ mixes and podcasts, which are crowdsourced "
"by its registered users. Its notable users include Wired, Harvard Business "
"School, TED Talks, and Barack Obama. Mixcloud was originally funded by its "
"founders only and continues to be owned solely by its team.");
    return meta;
}

//---------------------------------------------------------
bool MixcloudPlugin::flashRequired()
{
    return true;
}

//---------------------------------------------------------
QUrl MixcloudPlugin::url() const
{
    return QUrl("http://mixcloud.com");
}

//---------------------------------------------------------
void MixcloudPlugin::play()
{
    qDebug() << "play";
#ifdef Q_OS_WIN32
    this->runJavaScript("$('.player-control').click()");
#else
    this->runJavaScript("$('.player-control').get()[0].click()");
#endif
    qApp->processEvents();
}

//---------------------------------------------------------
void MixcloudPlugin::pause()
{
    this->play();
}

//---------------------------------------------------------
void MixcloudPlugin::stop()
{
    this->pause();
}

//---------------------------------------------------------
void MixcloudPlugin::next()
{
    // not supported
}

//---------------------------------------------------------
void MixcloudPlugin::previous()
{
    // not supported
}

//---------------------------------------------------------
void MixcloudPlugin::seekToPosition(int position)
{
    Q_UNUSED(position);
}

//---------------------------------------------------------
PlaybackStatus MixcloudPlugin::playbackStatus()
{
    if(currentSongInfo().isValid())
        if(runJavaScript("$('.player-control').hasClass("
                          "'player-control pause-state')").toBool())
            return Playing;
        else if(runJavaScript("$('.player-control').hasClass("
                                 "'player-control loading-state')").toBool())
            return Buffering;
        else
            return Paused;
    else
        return Stopped;
}

//---------------------------------------------------------
SongInfo MixcloudPlugin::currentSongInfo()
{
    SongInfo retVal;
    // prefer current track over the playlist title if available, not
    // all playlist have track bindings.
    retVal.songName = runJavaScript("$('.current-track').text()").toString();
    if(retVal.isValid())
    {
        retVal.artistName = runJavaScript(
            "$('.current-artist').children(0).html()").toString();
        retVal.albumName = runJavaScript(
            "$('.player-cloudcast-title').get()[0].text").toString();
    }
    else
    {
        retVal.songName = runJavaScript(
            "$('.player-cloudcast-title').get()[0].text").toString();
        retVal.artistName = runJavaScript(
            "$('.player-cloudcast-author-link').get()[0].text").toString();
    }
    if(retVal.isValid())
    {
        retVal.artUrl = runJavaScript(
            "$('.player-cloudcast-image').children(0).get(0).src")
                .toString().replace("w/60/h/60", "w/500/h/500");
        retVal.songId = QFileInfo(retVal.artUrl).baseName().replace("-", "");

        // cannot seek
        retVal.position = 0;
        retVal.duration = 0;
    }
    return retVal;
}

//---------------------------------------------------------
float MixcloudPlugin::volume()
{
    return 1.f;
}

//---------------------------------------------------------
void MixcloudPlugin::setVolume(float volume)
{
    Q_UNUSED(volume);
}

//---------------------------------------------------------
bool MixcloudPlugin::canFavorite()
{
    return true;
}

//---------------------------------------------------------
bool MixcloudPlugin::isFavorite()
{
    return !runJavaScript(
        "$('.icon-favorite-inner').get(0).getAttribute('class')")
            .toString().contains("ng-hide");
}

//---------------------------------------------------------
void MixcloudPlugin::addToFavorite(bool add)
{
    Q_UNUSED(add);
    runJavaScript("$('.icon-favorite-inner').get(0).click()");
}

//---------------------------------------------------------
bool MixcloudPlugin::canSeek()
{
    return false;
}

//---------------------------------------------------------
bool MixcloudPlugin::canGoNext()
{
    return false;
}

//---------------------------------------------------------
bool MixcloudPlugin::canGoPrevious()
{
    return false;
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( MixcloudPlugin, MixcloudPlugin )
#endif
