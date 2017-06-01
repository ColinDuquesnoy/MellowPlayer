#include <qxtglobalshortcut.h>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include "HotkeysService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

HotkeysService::HotkeysService(IPlayer& player, Settings& settings) :
        QObject(nullptr),
        logger(LoggingManager::instance().getLogger("Hotkeys")),
        player(player),
        playShortcutSetting(settings.get(SettingKey::SHORTCUTS_PLAY)),
        nextShortcutSetting(settings.get(SettingKey::SHORTCUTS_NEXT)),
        previousShortcutSetting(settings.get(SettingKey::SHORTCUTS_PREVIOUS)),
        favoriteShortcutSetting(settings.get(SettingKey::SHORTCUTS_FAVORITE)) {
    connect(&playShortcutSetting, &Setting::valueChanged, this, &HotkeysService::updatePlayShortcut);
    connect(&nextShortcutSetting, &Setting::valueChanged, this, &HotkeysService::updateNextShortcut);
    connect(&previousShortcutSetting, &Setting::valueChanged, this, &HotkeysService::updatePreviousShorcut);
    connect(&favoriteShortcutSetting, &Setting::valueChanged, this, &HotkeysService::updateFavoriteShortcut);
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

void HotkeysService::start() {

    playShortcut = new QxtGlobalShortcut(this);
    updatePlayShortcut();
    connect(playShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::togglePlayPause);

    nextShortcut = new QxtGlobalShortcut(this);
    updateNextShortcut();
    connect(nextShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::next);

    previousShortcut = new QxtGlobalShortcut(this);
    updatePreviousShorcut();
    connect(previousShortcut, &QxtGlobalShortcut::activated, this, &HotkeysService::previous);

    favoriteShortcut = new QxtGlobalShortcut(this);
    updateFavoriteShortcut();
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
}

void HotkeysService::updatePlayShortcut() const {
    playShortcut->setShortcut(QKeySequence(playShortcutSetting.getValue().toString()));
}

void HotkeysService::updateNextShortcut() const {
    nextShortcut->setShortcut(QKeySequence(nextShortcutSetting.getValue().toString()));
}

void HotkeysService::updatePreviousShorcut() const {
    previousShortcut->setShortcut(QKeySequence(previousShortcutSetting.getValue().toString()));
}

void HotkeysService::updateFavoriteShortcut() const {
    favoriteShortcut->setShortcut(QKeySequence(favoriteShortcutSetting.getValue().toString()));
}
