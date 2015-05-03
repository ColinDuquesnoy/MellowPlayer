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

#include "%(name)s.h"

//---------------------------------------------------------
%(classname)s::%(classname)s()
{
    Q_INIT_RESOURCE(%(name)s);
}

//---------------------------------------------------------
bool %(classname)s::flashRequired()
{
    // most services require flash, change it to false if you're
    // working on an html5 service.
    return true;
}


//---------------------------------------------------------
const PluginMetaData &%(classname)s::metaData() const
{
    static PluginMetaData meta;
    meta.name = "%(name_cap)s";
    meta.author = "YOUR NAME";
    meta.author_website = "YOUR GITHUB PROFILE URL";
    meta.version = "1.0";
    meta.icon = QIcon("YOUR ICON PATH");
    meta.description =tr("Music streaming service description");
    return meta;
}

//---------------------------------------------------------
QUrl %(classname)s::url() const
{
    return QUrl("YOUR SERVICE URL");
}

//---------------------------------------------------------
void %(classname)s::play()
{
    this->runJavaScript("");
}

//---------------------------------------------------------
void %(classname)s::pause()
{
    this->runJavaScript("");
}

//---------------------------------------------------------
void %(classname)s::next()
{
    this->runJavaScript("");
}

//---------------------------------------------------------
void %(classname)s::previous()
{
    this->runJavaScript("");
}

//---------------------------------------------------------
void %(classname)s::seekToPosition(int position)
{
    Q_UNUSED(position);
}

//---------------------------------------------------------
PlaybackStatus %(classname)s::playbackStatus()
{
    return Stopped;
}

//---------------------------------------------------------
SongInfo %(classname)s::currentSongInfo()
{
    SongInfo retVal;
    return retVal;
}

//---------------------------------------------------------
float %(classname)s::volume()
{
    return 1.f;
}

//---------------------------------------------------------
void %(classname)s::setVolume(float volume)
{
    Q_UNUSED(volume);
}

//---------------------------------------------------------
bool %(classname)s::canFavorite()
{
    return false;
}

//---------------------------------------------------------
bool %(classname)s::isFavorite()
{
    return false;
}

//---------------------------------------------------------
void %(classname)s::addToFavorite(bool add)
{
    Q_UNUSED(add);
}

//---------------------------------------------------------
bool %(classname)s::canSeek()
{
    return false;
}

//---------------------------------------------------------
bool %(classname)s::canGoNext()
{
    return true;
}

//---------------------------------------------------------
bool %(classname)s::canGoPrevious()
{
    return true;
}


