#pragma once

#include "NotificationFactory.hpp"
#include <MellowPlayer/Domain/Notifications/INotifier.hpp>
#include <QObject>

namespace MellowPlayer::Domain
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
    class Notifier : public QObject, public Domain::INotifier
    {
        Q_OBJECT
    public:
        Notifier(Domain::IPlayer& player, Domain::ILocalAlbumArt& localAlbumArtService, Domain::INotificationPresenter& presenter,
                 Domain::StreamingServicesController& streamingServices, Domain::Settings& settings);

        void initialize() override;
        bool display(const Domain::Notification& notification) override;

    public slots:
        void onCurrentSongChanged(Domain::Song* song);
        void onPlaybackStatusChanged();
        void onCurrentSongUrlChanged();

    private:
        void showSongNotification(Domain::Song* song, const QString& localAlbumArtUrl);
        bool isPlaying() const;
        const QString currentServiceName() const;
        const QString currentServiceLogo() const;
        bool isNotificationTypeEnabled(Domain::NotificationType type) const;

        Domain::ILogger& logger_;
        Domain::IPlayer& player_;
        Domain::ILocalAlbumArt& localAlbumArtService_;
        Domain::INotificationPresenter& presenter_;
        Domain::StreamingServicesController& streamingServices_;
        Domain::Settings& settings_;
        Domain::Notification previousNotif_;
        NotificationFactory notificationFactory_;
        QString previousSongId_;
    };
}
