#include <MellowPlayer/Presentation/Mpris/Linux/Mpris2Root.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

Mpris2Root::Mpris2Root(IMainWindow& mainWindow, QObject* parent)
        : QDBusAbstractAdaptor(parent), logger_(Loggers::logger("Mpris2Root")), mainWindow_(mainWindow)
{
}

void Mpris2Root::Raise()
{
    mainWindow_.show();
}

void Mpris2Root::Quit()
{
    mainWindow_.requestQuit();
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

