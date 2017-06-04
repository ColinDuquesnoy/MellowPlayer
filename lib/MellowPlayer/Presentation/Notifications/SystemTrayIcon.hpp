#pragma once

#include <QSystemTrayIcon>
#include <QMenu>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Utils/IconProvider.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Setting)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SystemTrayIcon: public QObject, public Application::ISystemTrayIcon {
    Q_OBJECT
public:
    SystemTrayIcon(Application::IPlayer& player, Application::IMainWindow& mainWindow,
                   Application::IQtApplication& qtApplication, Application::Settings& settings);
    void show() override;
    void hide() override;
    void showMessage(const QString &title, const QString &message) override;

public slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void togglePlayPause();
    void next();
    void previous();
    void restoreWindow();
    void quit();

private slots:
    void onShowTrayIconSettingValueChanged();

private:
    void setUpMenu();

    Application::ILogger& logger;
    Application::IPlayer& player;
    Application::IMainWindow& mainWindow;
    Application::IQtApplication& qtApplication;
    Application::Settings& settings;
    Application::Setting& showTrayIconSetting;

    QSystemTrayIcon qSystemTrayIcon;
    QMenu menu;
    QAction* playPauseAction;
    QAction* previousSongAction;
    QAction* nextSongAction;
    QAction* restoreWindowAction;
    QAction* quitApplicationAction;
};

END_MELLOWPLAYER_NAMESPACE
