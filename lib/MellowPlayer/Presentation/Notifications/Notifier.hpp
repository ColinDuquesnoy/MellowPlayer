#pragma once

#include "NotificationFactory.hpp"
#include <MellowPlayer/Application/Notifications/INotifier.hpp>
#include <QObject>

namespace MellowPlayer::Application
{
    class Settings;
    class ILogger;
    class ILocalAlbumArt;
    class IPlayer;
    class INotificationPresenter;
    class StreamingServicesController;
    class Song;
}

namespace MellowPlayer::Presentation
{
    class Notifier : public QObject, public Application::INotifier
    {
        Q_OBJECT
    public:
        Notifier(Application::IPlayer& player, Application::ILocalAlbumArt& localAlbumArtService, Application::INotificationPresenter& presenter,
                 Application::StreamingServicesController& streamingServices, Application::Settings& settings);

        void initialize() override;
        bool display(const Application::Notification& notification) override;

    public slots:
        void onCurrentSongChanged(Application::Song* song);
        void onPlaybackStatusChanged();
        void onCurrentSongUrlChanged();

    private:
        void showSongNotification(Application::Song* song, const QString& localAlbumArtUrl);
        bool isPlaying() const;
        const QString currentServiceName() const;
        const QString currentServiceLogo() const;
        bool isNotificationTypeEnabled(Application::NotificationType type) const;

        Application::ILogger& logger_;
        Application::IPlayer& player_;
        Application::ILocalAlbumArt& localAlbumArtService_;
        Application::INotificationPresenter& presenter_;
        Application::StreamingServicesController& streamingServices_;
        Application::Settings& settings_;
        Application::Notification previousNotif_;
        NotificationFactory notificationFactory_;
        QString previousSongId_;
    };
}
