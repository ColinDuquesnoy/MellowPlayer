#include "Hotkeys.hpp"
#include <MellowPlayer/Domain/IMainWindow.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <qxtglobalshortcut.h>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

Hotkeys::Hotkeys(IPlayer& player, Settings& settings, IMainWindow& application)
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
    connect(&playShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updatePlayShortcut);
    connect(&nextShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updateNextShortcut);
    connect(&previousShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updatePreviousShorcut);
    connect(&favoriteShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updateFavoriteShortcut);
    connect(&restoreWindowShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updateRestoreWindowShortcut);
}

void Hotkeys::togglePlayPause()
{
    player_.togglePlayPause();
}

void Hotkeys::next()
{
    player_.next();
}

void Hotkeys::previous()
{
    player_.previous();
}

void Hotkeys::toggleFavoriteSong()
{
    player_.toggleFavoriteSong();
}

Hotkeys::~Hotkeys()
{
}

void Hotkeys::start()
{

    playShortcut_ = new QxtGlobalShortcut(this);
    updatePlayShortcut();
    connect(playShortcut_, &QxtGlobalShortcut::activated, this, &Hotkeys::togglePlayPause);

    nextShortcut_ = new QxtGlobalShortcut(this);
    updateNextShortcut();
    connect(nextShortcut_, &QxtGlobalShortcut::activated, this, &Hotkeys::next);

    previousShortcut_ = new QxtGlobalShortcut(this);
    updatePreviousShorcut();
    connect(previousShortcut_, &QxtGlobalShortcut::activated, this, &Hotkeys::previous);

    favoriteShortcut_ = new QxtGlobalShortcut(this);
    updateFavoriteShortcut();
    connect(favoriteShortcut_, &QxtGlobalShortcut::activated, this, &Hotkeys::toggleFavoriteSong);

    restoreWindowShortcut_ = new QxtGlobalShortcut(this);
    updateRestoreWindowShortcut();
    connect(restoreWindowShortcut_, &QxtGlobalShortcut::activated, this, &Hotkeys::restoreWindow);

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

void Hotkeys::updatePlayShortcut() const
{
    playShortcut_->setShortcut(QKeySequence(playShortcutSetting_.value().toString()));
}

void Hotkeys::updateNextShortcut() const
{
    nextShortcut_->setShortcut(QKeySequence(nextShortcutSetting_.value().toString()));
}

void Hotkeys::updatePreviousShorcut() const
{
    previousShortcut_->setShortcut(QKeySequence(previousShortcutSetting_.value().toString()));
}

void Hotkeys::updateFavoriteShortcut() const
{
    favoriteShortcut_->setShortcut(QKeySequence(favoriteShortcutSetting_.value().toString()));
}

void Hotkeys::restoreWindow()
{
    mainWindow_.show();
}

void Hotkeys::updateRestoreWindowShortcut() const
{
    restoreWindowShortcut_->setShortcut(QKeySequence(restoreWindowShortcutSetting_.value().toString()));
}
