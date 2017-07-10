#include <qxtglobalshortcut.h>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include "HotkeysController.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

HotkeysController::HotkeysController(IPlayer& player, Settings& settings) :
        QObject(nullptr),
        logger(LoggingManager::instance().getLogger("Hotkeys")),
        player(player),
        playShortcutSetting(settings.get(SettingKey::SHORTCUTS_PLAY)),
        nextShortcutSetting(settings.get(SettingKey::SHORTCUTS_NEXT)),
        previousShortcutSetting(settings.get(SettingKey::SHORTCUTS_PREVIOUS)),
        favoriteShortcutSetting(settings.get(SettingKey::SHORTCUTS_FAVORITE)) {
    connect(&playShortcutSetting, &Setting::valueChanged, this, &HotkeysController::updatePlayShortcut);
    connect(&nextShortcutSetting, &Setting::valueChanged, this, &HotkeysController::updateNextShortcut);
    connect(&previousShortcutSetting, &Setting::valueChanged, this, &HotkeysController::updatePreviousShorcut);
    connect(&favoriteShortcutSetting, &Setting::valueChanged, this, &HotkeysController::updateFavoriteShortcut);
}

void HotkeysController::togglePlayPause() {
    player.togglePlayPause();
}

void HotkeysController::next() {
    player.next();
}

void HotkeysController::previous() {
    player.previous();
}

void HotkeysController::toggleFavoriteSong() {
    player.toggleFavoriteSong();
}

HotkeysController::~HotkeysController() {

}

void HotkeysController::start() {

    playShortcut = new QxtGlobalShortcut(this);
    updatePlayShortcut();
    connect(playShortcut, &QxtGlobalShortcut::activated, this, &HotkeysController::togglePlayPause);

    nextShortcut = new QxtGlobalShortcut(this);
    updateNextShortcut();
    connect(nextShortcut, &QxtGlobalShortcut::activated, this, &HotkeysController::next);

    previousShortcut = new QxtGlobalShortcut(this);
    updatePreviousShorcut();
    connect(previousShortcut, &QxtGlobalShortcut::activated, this, &HotkeysController::previous);

    favoriteShortcut = new QxtGlobalShortcut(this);
    updateFavoriteShortcut();
    connect(favoriteShortcut, &QxtGlobalShortcut::activated, this, &HotkeysController::toggleFavoriteSong);

#ifdef Q_OS_WIN
    auto mediaShortcut = new QxtGlobalShortcut(this);
    mediaShortcut->setShortcut(QKeySequence(Qt::Key_MediaPlay));
    connect(mediaShortcut, &QxtGlobalShortcut::activated, this, &HotkeysController::togglePlayPause);

    mediaShortcut = new QxtGlobalShortcut(this);
    mediaShortcut->setShortcut(QKeySequence(Qt::Key_MediaNext));
    connect(mediaShortcut, &QxtGlobalShortcut::activated, this, &HotkeysController::next);

    mediaShortcut = new QxtGlobalShortcut(this);
    mediaShortcut->setShortcut(QKeySequence(Qt::Key_MediaPrevious));
    connect(mediaShortcut, &QxtGlobalShortcut::activated, this, &HotkeysController::previous);
#endif

    LOG_DEBUG(logger, "service started");
}

void HotkeysController::updatePlayShortcut() const {
    playShortcut->setShortcut(QKeySequence(playShortcutSetting.getValue().toString()));
}

void HotkeysController::updateNextShortcut() const {
    nextShortcut->setShortcut(QKeySequence(nextShortcutSetting.getValue().toString()));
}

void HotkeysController::updatePreviousShorcut() const {
    previousShortcut->setShortcut(QKeySequence(previousShortcutSetting.getValue().toString()));
}

void HotkeysController::updateFavoriteShortcut() const {
    favoriteShortcut->setShortcut(QKeySequence(favoriteShortcutSetting.getValue().toString()));
}
