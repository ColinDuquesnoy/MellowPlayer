#pragma once

#include <QSystemTrayIcon>
#include <QMenu>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Utils/IconProvider.hpp>

namespace MellowPlayer::Application {

    class ILogger;
    class IPlayer;
    class IMainWindow;
    class IQtApplication;
    class Setting;
    class Settings;

}

namespace MellowPlayer::Presentation {

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

}
