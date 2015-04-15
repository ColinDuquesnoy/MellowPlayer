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

#include <QMainWindow>
#include <mellowplayer.h>
#include "mpris2root.h"

//---------------------------------------------------------
Mpris2Root::Mpris2Root(QObject *parent):
    QDBusAbstractAdaptor(parent)
{

}

//---------------------------------------------------------
void Mpris2Root::Raise()
{
    Services::raiseMainWindow();
}

//---------------------------------------------------------
void Mpris2Root::Quit()
{
    qApp->exit(0);
}

//---------------------------------------------------------
bool Mpris2Root::canRaise()
{
    return true;
}

//---------------------------------------------------------
bool Mpris2Root::canQuit()
{
    return true;
}

//---------------------------------------------------------
bool Mpris2Root::hasTrackList()
{
    return false;
}

//---------------------------------------------------------
bool Mpris2Root::canSetFullscreen()
{
    return true;
}

//---------------------------------------------------------
bool Mpris2Root::fullscreen()
{
    return Services::mainWindow()->isFullScreen();
}

//---------------------------------------------------------
void Mpris2Root::setFullscreen(bool value)
{
    if(value)
        Services::mainWindow()->showFullScreen();
    else
        Services::mainWindow()->showNormal();
}

//---------------------------------------------------------
QString Mpris2Root::identity()
{
    return "MellowPlayer";
}

//---------------------------------------------------------
QString Mpris2Root::desktopEntry()
{
    return "mellowplayer";
}

//---------------------------------------------------------
QStringList Mpris2Root::supportedUriSchemes()
{
    QStringList retVal;
    retVal.append("http");
    return retVal;
}

//---------------------------------------------------------
QStringList Mpris2Root::supportedMimeTypes()
{
    return QStringList();
}

