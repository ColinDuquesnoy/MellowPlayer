#include <qxtglobalshortcut.h>
#include "Hotkeys.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

Hotkeys::Hotkeys(IPlayer& player): player(player) {

    playShortcut = new QxtGlobalShortcut(this);
    playShortcut->setShortcut(QKeySequence("Ctrl+Alt+P"));
    connect(playShortcut, &QxtGlobalShortcut::activated, this, &Hotkeys::togglePlayPause);

    nextShortcut = new QxtGlobalShortcut(this);
    nextShortcut->setShortcut(QKeySequence("Ctrl+Alt+N"));
    connect(nextShortcut, &QxtGlobalShortcut::activated, this, &Hotkeys::next);

    previousShortcut = new QxtGlobalShortcut(this);
    previousShortcut->setShortcut(QKeySequence("Ctrl+Alt+B"));
    connect(previousShortcut, &QxtGlobalShortcut::activated, this, &Hotkeys::previous);

    favoriteShortcut = new QxtGlobalShortcut(this);
    favoriteShortcut->setShortcut(QKeySequence("Ctrl+Alt+F"));
    connect(favoriteShortcut, &QxtGlobalShortcut::activated, this, &Hotkeys::toggleFavoriteSong);
}

void Hotkeys::togglePlayPause() {
    player.togglePlayPause();
}

void Hotkeys::next() {
    player.next();
}

void Hotkeys::previous() {
    player.previous();
}

void Hotkeys::toggleFavoriteSong() {
    player.toggleFavoriteSong();
}
