#include <qxtglobalshortcut.h>
#include "HotkeysService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

HotkeysService::HotkeysService(IPlayer& player) :
    QObject(nullptr), logger(LoggingManager::instance().getLogger("Hotkeys")), player(player) {

}

bool HotkeysService::start() {
    playShortcut = new QxtGlobalShortcut(this);
    playShortcut->setShortcut(QKeySequence("Ctrl+Alt+P"));
    connect(playShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::togglePlayPause);

    nextShortcut = new QxtGlobalShortcut(this);
    nextShortcut->setShortcut(QKeySequence("Ctrl+Alt+N"));
    connect(nextShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::next);

    previousShortcut = new QxtGlobalShortcut(this);
    previousShortcut->setShortcut(QKeySequence("Ctrl+Alt+B"));
    connect(previousShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::previous);

    favoriteShortcut = new QxtGlobalShortcut(this);
    favoriteShortcut->setShortcut(QKeySequence("Ctrl+Alt+F"));
    connect(favoriteShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::toggleFavoriteSong);

#ifdef Q_OS_WIN
    auto mediaShortcut = new QxtGlobalShortcut(this);
    mediaShortcut->setShortcut(QKeySequence(Qt::Key_MediaPlay));
    connect(mediaShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::togglePlayPause);

    mediaShortcut = new QxtGlobalShortcut(this);
    mediaShortcut->setShortcut(QKeySequence(Qt::Key_MediaNext));
    connect(mediaShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::next);

    mediaShortcut = new QxtGlobalShortcut(this);
    mediaShortcut->setShortcut(QKeySequence(Qt::Key_MediaPrevious));
    connect(mediaShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::previous);
#endif

    LOG_INFO(logger, "service started");
    return true;
}

void HotkeysService::togglePlayPause() {
    player.togglePlayPause();
}

void HotkeysService::next() {
    player.next();
}

void HotkeysService::previous() {
    player.previous();
}

void HotkeysService::toggleFavoriteSong() {
    player.toggleFavoriteSong();
}

HotkeysService::~HotkeysService() {

}
