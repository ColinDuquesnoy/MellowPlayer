#include "SystemTrayIcon.hpp"
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <MellowPlayer/Application/IQtApplication.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/SettingKey.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

SystemTrayIcon::SystemTrayIcon(IPlayer& player, IMainWindow& mainWindow, IQtApplication& qtApplication, Settings& settings)
        : QObject(),
          logger_(LoggingManager::logger("SystemTrayIcon")),
          player_(player),
          mainWindow_(mainWindow),
          qtApp_(qtApplication),
          settings_(settings),
          showTrayIconSetting_(settings.get(SettingKey::MAIN_SHOW_TRAY_ICON)),
          qSystemTrayIcon_(IconProvider::trayIcon())
{
    connect(&qSystemTrayIcon_, &QSystemTrayIcon::activated, this, &SystemTrayIcon::onActivated);
    connect(&showTrayIconSetting_, &Setting::valueChanged, this, &SystemTrayIcon::onShowTrayIconSettingValueChanged);
    setUpMenu();
}

void SystemTrayIcon::show()
{
    LOG_DEBUG(logger_, "show");
    if (showTrayIconSetting_.value().toBool())
        qSystemTrayIcon_.show();
}

void SystemTrayIcon::hide()
{
    LOG_DEBUG(logger_, "hide");
    qSystemTrayIcon_.hide();
}

void SystemTrayIcon::showMessage(const QString& title, const QString& message)
{
    LOG_DEBUG(logger_, "show message: " + title + " - " + message);
    qSystemTrayIcon_.showMessage(title, message);
}

void SystemTrayIcon::onActivated(QSystemTrayIcon::ActivationReason)
{
    LOG_TRACE(logger_, "activated");
    mainWindow_.show();
}

void SystemTrayIcon::setUpMenu()
{
    SystemTrayIconStrings strings;
    playPauseAction_ = menu_.addAction(IconProvider::play(), strings.playPause());
    connect(playPauseAction_, &QAction::triggered, this, &SystemTrayIcon::togglePlayPause);

    nextSongAction_ = menu_.addAction(IconProvider::next(), strings.next());
    connect(nextSongAction_, &QAction::triggered, this, &SystemTrayIcon::next);

    previousSongAction_ = menu_.addAction(IconProvider::previous(), strings.previous());
    connect(previousSongAction_, &QAction::triggered, this, &SystemTrayIcon::previous);

    menu_.addSeparator();

    restoreWindowAction_ = menu_.addAction(IconProvider::restoreWindow(), strings.restoreWindow());
    connect(restoreWindowAction_, &QAction::triggered, this, &SystemTrayIcon::restoreWindow);

    menu_.addSeparator();

    quitApplicationAction_ = menu_.addAction(IconProvider::quit(), strings.quit());
    connect(quitApplicationAction_, &QAction::triggered, this, &SystemTrayIcon::quit);

    qSystemTrayIcon_.setContextMenu(&menu_);
}

void SystemTrayIcon::togglePlayPause()
{
    LOG_TRACE(logger_, "togglePlayPause");
    player_.togglePlayPause();
}

void SystemTrayIcon::next()
{
    LOG_TRACE(logger_, "next");
    player_.next();
}

void SystemTrayIcon::previous()
{
    LOG_TRACE(logger_, "previous");
    player_.previous();
}

void SystemTrayIcon::restoreWindow()
{
    LOG_TRACE(logger_, "restore window");
    mainWindow_.show();
}

void SystemTrayIcon::quit()
{
    LOG_TRACE(logger_, "quit");
    qtApp_.requestQuit();
}

void SystemTrayIcon::onShowTrayIconSettingValueChanged()
{
    if (showTrayIconSetting_.value().toBool())
        show();
    else
        hide();
}

QString SystemTrayIconStrings::playPause() const
{
    return tr("Play/Pause");
}

QString SystemTrayIconStrings::next() const
{
    return tr("Next");
}

QString SystemTrayIconStrings::previous() const
{
    return tr("Previous");
}

QString SystemTrayIconStrings::restoreWindow() const
{
    return tr("Restore window");
}

QString SystemTrayIconStrings::quit() const
{
    return tr("Quit");
}

