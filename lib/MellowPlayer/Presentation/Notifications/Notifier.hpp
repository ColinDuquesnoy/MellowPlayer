#pragma once

#include <MellowPlayer/Application/Notifications/INotifier.hpp>
#include "NotificationFactory.hpp"

namespace MellowPlayer::Application {

    class Settings;
    class ILogger;
    class ILocalAlbumArt;
    class IPlayer;
    class INotificationPresenter;
    class StreamingServicesController;

}

namespace MellowPlayer::Presentation {

    class Notifier: public QObject, public Application::INotifier {
        Q_OBJECT
    public:
        Notifier(Application::IPlayer& player, Application::ILocalAlbumArt& localAlbumArtService,
                            Application::INotificationPresenter& presenter, Application::StreamingServicesController& streamingServices,
                            Application::Settings& settings);

        void initialize() override;
        bool display(const Application::Notification& notification) override;

    public slots:
        void onCurrentSongChanged(Application::Song* song);
        void onPlaybackStatusChanged();
        void onCurrentSongUrlChanged();

    private:
        void showSongNotification(Application::Song* song, const QString& localAlbumArtUrl);
        bool isPlaying() const;
        const QString getCurrentServiceName() const;
        const QString getCurrentServiceLogo() const;
        bool isNotificationTypeEnabled(Application::NotificationType type) const;

        Application::ILogger& logger;
        Application::IPlayer& player;
        Application::ILocalAlbumArt& localAlbumArtService;
        Application::INotificationPresenter& presenter;
        Application::StreamingServicesController& streamingServices;
        Application::Settings& settings;
        Application::Notification previousNotif;
        NotificationFactory notificationFactory;
        QString previousSongId;
    };

}
