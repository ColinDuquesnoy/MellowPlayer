#include "Mpris2Root.hpp"

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

Mpris2Root::Mpris2Root(QQuickWindow* window, QObject* parent)
    : QDBusAbstractAdaptor(parent), window(window) {

}

void Mpris2Root::Raise() {
    if (window != nullptr) {
        window->show();
        window->raise();
    }
}

// LCOV_EXCL_START
void Mpris2Root::Quit() {
    qApp->exit(0);
}
// LCOV_EXCL_STOP

bool Mpris2Root::canRaise() {
    return true;
}

bool Mpris2Root::canQuit() {
    return true;
}

bool Mpris2Root::hasTrackList() {
    return false;
}

bool Mpris2Root::canSetFullscreen() {
    return false;
}

bool Mpris2Root::fullscreen() {
    return false;
}

void Mpris2Root::setFullscreen(bool value) {
    Q_UNUSED(value);
}

QString Mpris2Root::identity() {
    return "MellowPlayer";
}

QString Mpris2Root::desktopEntry() {
    return "mellowplayer";
}

QStringList Mpris2Root::supportedUriSchemes() {
    return QStringList();
}

QStringList Mpris2Root::supportedMimeTypes() {
    return QStringList();
}
