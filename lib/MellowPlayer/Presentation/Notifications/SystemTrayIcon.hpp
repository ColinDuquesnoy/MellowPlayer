#pragma once

#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <QMenu>
#include <QSystemTrayIcon>

namespace MellowPlayer::Domain
{
    class ILogger;
    class IPlayer;
    class Setting;
    class Settings;
}

class SystemTrayIconStrings : public QObject
{
    Q_OBJECT
public:
    QString playPause() const;
    QString next() const;
    QString previous() const;
    QString restoreWindow() const;
    QString quit() const;
};

namespace MellowPlayer::Infrastructure
{
    class IApplication;
}

namespace MellowPlayer::Presentation
{
    class IMainWindow;

    class SystemTrayIcon : public QObject, public ISystemTrayIcon
    {
        Q_OBJECT
    public:
        SystemTrayIcon(Domain::IPlayer& player, IMainWindow& mainWindow, Domain::Settings& settings);

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

        Domain::ILogger& logger_;
        Domain::IPlayer& player_;
        IMainWindow& mainWindow_;
        Domain::Settings& settings_;
        Domain::Setting& showTrayIconSetting_;

        QSystemTrayIcon qSystemTrayIcon_;
        QMenu menu_;
        QAction* playPauseAction_;
        QAction* previousSongAction_;
        QAction* nextSongAction_;
        QAction* restoreWindowAction_;
        QAction* quitApplicationAction_;
    };
}
