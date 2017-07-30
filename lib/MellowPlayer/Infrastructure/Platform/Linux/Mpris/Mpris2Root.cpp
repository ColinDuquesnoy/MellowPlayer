#include "Mpris2Root.hpp"
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <MellowPlayer/Application/IQtApplication.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

Mpris2Root::Mpris2Root(IMainWindow& window, IQtApplication& qtApp, QObject* parent)
        : QDBusAbstractAdaptor(parent), logger_(LoggingManager::logger("Mpris2Root")), window_(window), qtApp_(qtApp)
{
}

void Mpris2Root::Raise()
{
    window_.show();
}

void Mpris2Root::Quit()
{
    qtApp_.requestQuit();
}

bool Mpris2Root::canRaise()
{
    return true;
}

bool Mpris2Root::canQuit()
{
    return true;
}

bool Mpris2Root::hasTrackList()
{
    return false;
}

bool Mpris2Root::canSetFullscreen()
{
    return false;
}

bool Mpris2Root::fullscreen()
{
    return false;
}

void Mpris2Root::setFullscreen(bool value)
{
    Q_UNUSED(value);
}

QString Mpris2Root::identity()
{
    return "MellowPlayer";
}

QString Mpris2Root::desktopEntry()
{
    return "mellowplayer";
}

QStringList Mpris2Root::supportedUriSchemes()
{
    return QStringList();
}

QStringList Mpris2Root::supportedMimeTypes()
{
    return QStringList();
}
