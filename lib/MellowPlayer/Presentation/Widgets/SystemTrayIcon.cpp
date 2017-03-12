#include "SystemTrayIcon.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

SystemTrayIcon::SystemTrayIcon(IPlayer& player, IMainWindow& mainWindow, IQtApplication& qtApplication,
                               IApplicationSettings& applicationSettings) :
        QObject(), logger(LoggingManager::instance().getLogger("SystemTrayIcon")),
        player(player), mainWindow(mainWindow), qtApplication(qtApplication),
        applicationSettings(applicationSettings), iconProvider(applicationSettings),
        qSystemTrayIcon(iconProvider.trayIcon()) {
    connect(&qSystemTrayIcon, &QSystemTrayIcon::activated, this, &SystemTrayIcon::onActivated);

    setUpMenu();
}

void SystemTrayIcon::show() {
    LOG_DEBUG(logger, "show");
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
    playPauseAction = menu.addAction(iconProvider.play(), "Play/Pause");
    connect(playPauseAction, &QAction::triggered, this, &SystemTrayIcon::togglePlayPause);

    nextSongAction = menu.addAction(iconProvider.next(), "Next");
    connect(nextSongAction, &QAction::triggered, this, &SystemTrayIcon::next);

    previousSongAction = menu.addAction(iconProvider.previous(), "Previous");
    connect(previousSongAction, &QAction::triggered, this, &SystemTrayIcon::previous);

    menu.addSeparator();

    restoreWindowAction = menu.addAction(iconProvider.restoreWindow(), "Restore window");
    connect(restoreWindowAction, &QAction::triggered, this, &SystemTrayIcon::restoreWindow);

    menu.addSeparator();

    quitApplicationAction = menu.addAction(iconProvider.quit(), "Quit");
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
    qtApplication.quit();
}
