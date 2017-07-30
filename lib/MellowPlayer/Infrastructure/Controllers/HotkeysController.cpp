#include "HotkeysController.hpp"
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <qxtglobalshortcut.h>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

HotkeysController::HotkeysController(IPlayer& player, Settings& settings, IMainWindow& application)
        : QObject(nullptr),
          logger_(LoggingManager::logger("Hotkeys")),
          player_(player),
          mainWindow_(application),
          playShortcutSetting_(settings.get(SettingKey::SHORTCUTS_PLAY)),
          nextShortcutSetting_(settings.get(SettingKey::SHORTCUTS_NEXT)),
          previousShortcutSetting_(settings.get(SettingKey::SHORTCUTS_PREVIOUS)),
          favoriteShortcutSetting_(settings.get(SettingKey::SHORTCUTS_FAVORITE)),
          restoreWindowShortcutSetting_(settings.get(SettingKey::SHORTCUTS_RESTORE_WINDOW))
{
    connect(&playShortcutSetting_, &Setting::valueChanged, this, &HotkeysController::updatePlayShortcut);
    connect(&nextShortcutSetting_, &Setting::valueChanged, this, &HotkeysController::updateNextShortcut);
    connect(&previousShortcutSetting_, &Setting::valueChanged, this, &HotkeysController::updatePreviousShorcut);
    connect(&favoriteShortcutSetting_, &Setting::valueChanged, this, &HotkeysController::updateFavoriteShortcut);
    connect(&restoreWindowShortcutSetting_, &Setting::valueChanged, this, &HotkeysController::updateRestoreWindowShortcut);
}

void HotkeysController::togglePlayPause()
{
    player_.togglePlayPause();
}

void HotkeysController::next()
{
    player_.next();
}

void HotkeysController::previous()
{
    player_.previous();
}

void HotkeysController::toggleFavoriteSong()
{
    player_.toggleFavoriteSong();
}

HotkeysController::~HotkeysController()
{
}

void HotkeysController::start()
{

    playShortcut_ = new QxtGlobalShortcut(this);
    updatePlayShortcut();
    connect(playShortcut_, &QxtGlobalShortcut::activated, this, &HotkeysController::togglePlayPause);

    nextShortcut_ = new QxtGlobalShortcut(this);
    updateNextShortcut();
    connect(nextShortcut_, &QxtGlobalShortcut::activated, this, &HotkeysController::next);

    previousShortcut_ = new QxtGlobalShortcut(this);
    updatePreviousShorcut();
    connect(previousShortcut_, &QxtGlobalShortcut::activated, this, &HotkeysController::previous);

    favoriteShortcut_ = new QxtGlobalShortcut(this);
    updateFavoriteShortcut();
    connect(favoriteShortcut_, &QxtGlobalShortcut::activated, this, &HotkeysController::toggleFavoriteSong);

    restoreWindowShortcut_ = new QxtGlobalShortcut(this);
    updateRestoreWindowShortcut();
    connect(restoreWindowShortcut_, &QxtGlobalShortcut::activated, this, &HotkeysController::restoreWindow);

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

    LOG_DEBUG(logger_, "service started");
}

void HotkeysController::updatePlayShortcut() const
{
    playShortcut_->setShortcut(QKeySequence(playShortcutSetting_.value().toString()));
}

void HotkeysController::updateNextShortcut() const
{
    nextShortcut_->setShortcut(QKeySequence(nextShortcutSetting_.value().toString()));
}

void HotkeysController::updatePreviousShorcut() const
{
    previousShortcut_->setShortcut(QKeySequence(previousShortcutSetting_.value().toString()));
}

void HotkeysController::updateFavoriteShortcut() const
{
    favoriteShortcut_->setShortcut(QKeySequence(favoriteShortcutSetting_.value().toString()));
}

void HotkeysController::restoreWindow()
{
    mainWindow_.show();
}

void HotkeysController::updateRestoreWindowShortcut() const
{
    restoreWindowShortcut_->setShortcut(QKeySequence(restoreWindowShortcutSetting_.value().toString()));
}
