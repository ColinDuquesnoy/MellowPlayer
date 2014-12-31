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
#include <iostream>
#include <QtCore>
#include "grooveshark.h"


//---------------------------------------------------------
QUrl GroovesharkPlugin::url()
{
    return QUrl("http://grooveshark.com");
}

//---------------------------------------------------------
void GroovesharkPlugin::play()
{
    this->runJavaScript("window.Grooveshark.play();");
}

//---------------------------------------------------------
void GroovesharkPlugin::pause()
{
    this->runJavaScript("window.Grooveshark.pause();");
}

//---------------------------------------------------------
void GroovesharkPlugin::stop()
{
    this->pause();
}

//---------------------------------------------------------
void GroovesharkPlugin::next()
{
    this->runJavaScript("window.Grooveshark.next();");
}

//---------------------------------------------------------
void GroovesharkPlugin::previous()
{
    this->runJavaScript("window.Grooveshark.previous();");
}

//---------------------------------------------------------
SongInfo GroovesharkPlugin::currentSongInfo()
{
    return SongInfo();
}
