#pragma once

#include <MellowPlayer/UseCases/Interfaces/INotificationsService.hpp>
#include "NotificationFactory.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Settings)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILocalAlbumArtService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, INotificationPresenter)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, StreamingServicePluginService)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class NotificationService: public QObject, public UseCases::INotificationService {
    Q_OBJECT
public:
    NotificationService(UseCases::IPlayer& player, UseCases::ILocalAlbumArtService& localAlbumArtService,
                        UseCases::INotificationPresenter& presenter, UseCases::StreamingServicePluginService& pluginService,
                        UseCases::Settings& settings);

    void initialize() override;
    bool display(const Entities::Notification& notification) override;

public slots:
    void onCurrentSongChanged(Entities::Song* song);
    void onPlaybackStatusChanged();
    void onCurrentSongUrlChanged();

private:
    void showNewSongNotification(Entities::Song* song, const QString& localAlbumArtUrl);
    bool isPlaying() const;
    const QString getCurrentServiceName() const;
    const QString getCurrentServiceLogo() const;
    bool isNotificationTypeEnabled(Entities::NotificationType type) const;

    UseCases::ILogger& logger;
    UseCases::IPlayer& player;
    UseCases::ILocalAlbumArtService& localAlbumArtService;
    UseCases::INotificationPresenter& presenter;
    UseCases::StreamingServicePluginService& pluginService;
    UseCases::Settings& settings;
    Entities::Notification previousNotif;
    NotificationFactory notificationFactory;
};

END_MELLOWPLAYER_NAMESPACE
