#pragma once

#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/IconProvider.hpp>
#include <QMenu>
#include <QSystemTrayIcon>

namespace MellowPlayer::Application
{
    class ILogger;
    class IPlayer;
    class IMainWindow;
    class IQtApplication;
    class Setting;
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class SystemTrayIcon : public QObject, public Application::ISystemTrayIcon
    {
        Q_OBJECT
    public:
        SystemTrayIcon(Application::IPlayer& player, Application::IMainWindow& mainWindow, Application::IQtApplication& qtApplication,
                       Application::Settings& settings);
        void show() override;
        void hide() override;
        void showMessage(const QString& title, const QString& message) override;

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

        Application::ILogger& logger_;
        Application::IPlayer& player_;
        Application::IMainWindow& mainWindow_;
        Application::IQtApplication& qtApp_;
        Application::Settings& settings_;
        Application::Setting& showTrayIconSetting_;

        QSystemTrayIcon qSystemTrayIcon_;
        QMenu menu_;
        QAction* playPauseAction_;
        QAction* previousSongAction_;
        QAction* nextSongAction_;
        QAction* restoreWindowAction_;
        QAction* quitApplicationAction_;
    };
}
