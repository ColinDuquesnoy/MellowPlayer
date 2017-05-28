#include <MellowPlayer/UseCases/Interfaces/IQtApplication.hpp>
#include <MellowPlayer/UseCases/Interfaces/IMainWindow.hpp>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Player/IPlayer.hpp>
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/UseCases/Settings/Settings.hpp>
#include <MellowPlayer/UseCases/Settings/SettingKey.hpp>
#include "SystemTrayIcon.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

SystemTrayIcon::SystemTrayIcon(IPlayer& player, IMainWindow& mainWindow, IQtApplication& qtApplication,
                               Settings& settings) :
        QObject(), logger(LoggingManager::instance().getLogger("SystemTrayIcon")),
        player(player), mainWindow(mainWindow), qtApplication(qtApplication),
        settings(settings),
        showTrayIconSetting(settings.get(SettingKey::MAIN_SHOW_TRAY_ICON)),
        qSystemTrayIcon(IconProvider::trayIcon()) {
    connect(&qSystemTrayIcon, &QSystemTrayIcon::activated, this, &SystemTrayIcon::onActivated);
    connect(&showTrayIconSetting, &Setting::valueChanged, this, &SystemTrayIcon::onShowTrayIconSettingValueChanged);
    setUpMenu();
}

void SystemTrayIcon::show() {
    LOG_DEBUG(logger, "show");
    if (showTrayIconSetting.getValue().toBool())
        qSystemTrayIcon.show();
}

void SystemTrayIcon::hide() {
    LOG_DEBUG(logger, "hide");
    qSystemTrayIcon.hide();
}

void SystemTrayIcon::showMessage(const QString& title, const QString& message) {
    LOG_DEBUG(logger, "show message: " + title + " - " + message);
    qSystemTrayIcon.showMessage(title, message);
}

void SystemTrayIcon::onActivated(QSystemTrayIcon::ActivationReason) {
    LOG_TRACE(logger, "activated");
    mainWindow.show();
}

void SystemTrayIcon::setUpMenu() {
    playPauseAction = menu.addAction(IconProvider::play(), "Play/Pause");
    connect(playPauseAction, &QAction::triggered, this, &SystemTrayIcon::togglePlayPause);

    nextSongAction = menu.addAction(IconProvider::next(), "Next");
    connect(nextSongAction, &QAction::triggered, this, &SystemTrayIcon::next);

    previousSongAction = menu.addAction(IconProvider::previous(), "Previous");
    connect(previousSongAction, &QAction::triggered, this, &SystemTrayIcon::previous);

    menu.addSeparator();

    restoreWindowAction = menu.addAction(IconProvider::restoreWindow(), "Restore window");
    connect(restoreWindowAction, &QAction::triggered, this, &SystemTrayIcon::restoreWindow);

    menu.addSeparator();

    quitApplicationAction = menu.addAction(IconProvider::quit(), "Quit");
    connect(quitApplicationAction, &QAction::triggered, this, &SystemTrayIcon::quit);

    qSystemTrayIcon.setContextMenu(&menu);
}

void SystemTrayIcon::togglePlayPause() {
    LOG_TRACE(logger, "togglePlayPause");
    player.togglePlayPause();
}

void SystemTrayIcon::next() {
    LOG_TRACE(logger, "next");
    player.next();
}

void SystemTrayIcon::previous() {
    LOG_TRACE(logger, "previous");
    player.previous();
}

void SystemTrayIcon::restoreWindow() {
    LOG_TRACE(logger, "restore window");
    mainWindow.show();
}

void SystemTrayIcon::quit() {
    LOG_TRACE(logger, "quit");
    qtApplication.requestQuit();
}

void SystemTrayIcon::onShowTrayIconSettingValueChanged() {
    if (showTrayIconSetting.getValue().toBool())
        show();
    else
        hide();
}
