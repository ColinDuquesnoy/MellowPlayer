#pragma once

#include <QSystemTrayIcon>
#include <QMenu>
#include <MellowPlayer/UseCases.hpp>
#include "IconProvider.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SystemTrayIcon: public QObject, public UseCases::ISystemTrayIcon {
    Q_OBJECT
public:
    SystemTrayIcon(UseCases::IPlayer& player, UseCases::IMainWindow& mainWindow,
                   UseCases::IQtApplication& qtApplication, UseCases::IApplicationSettings& applicationSettings);
    void show() override;
    void hide() override;
    void showMessage(const QString &title, const QString &message) override;

private slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void togglePlayPause();
    void next();
    void previous();
    void restoreWindow();
    void quit();

private:
    void setUpMenu();
    UseCases::IPlayer& player;
    UseCases::IMainWindow& mainWindow;
    UseCases::IQtApplication& qtApplication;
    UseCases::IApplicationSettings& applicationSettings;
    IconProvider iconProvider;
    QSystemTrayIcon qSystemTrayIcon;
    QMenu menu;
    QAction* playPauseAction;
    QAction* previousSongAction;
    QAction* nextSongAction;
    QAction* restoreWindowAction;
    QAction* quitApplicationAction;
};

END_MELLOWPLAYER_NAMESPACE
