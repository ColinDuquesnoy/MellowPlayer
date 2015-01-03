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
    return "Mellow Player";
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

