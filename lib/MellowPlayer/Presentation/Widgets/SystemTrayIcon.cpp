#include "SystemTrayIcon.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

SystemTrayIcon::SystemTrayIcon(IPlayer& player, IMainWindow& mainWindow, IQtApplication& qtApplication,
                               IApplicationSettings& applicationSettings) :
        QObject(), player(player), mainWindow(mainWindow), qtApplication(qtApplication),
        applicationSettings(applicationSettings), iconProvider(applicationSettings),
        qSystemTrayIcon(iconProvider.trayIcon())
{
    connect(&qSystemTrayIcon, &QSystemTrayIcon::activated, this, &SystemTrayIcon::onActivated);

    setUpMenu();
}

void SystemTrayIcon::show() { qSystemTrayIcon.show(); }

void SystemTrayIcon::hide() { qSystemTrayIcon.hide(); }

void SystemTrayIcon::showMessage(const QString& title, const QString& message) {
    qSystemTrayIcon.showMessage(title, message);
}

void SystemTrayIcon::onActivated(QSystemTrayIcon::ActivationReason) { mainWindow.show(); }

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

void SystemTrayIcon::togglePlayPause() { player.togglePlayPause(); }

void SystemTrayIcon::next() { player.next(); }

void SystemTrayIcon::previous() { player.previous(); }

void SystemTrayIcon::restoreWindow() { mainWindow.show(); }

void SystemTrayIcon::quit() { qtApplication.quit(); }
