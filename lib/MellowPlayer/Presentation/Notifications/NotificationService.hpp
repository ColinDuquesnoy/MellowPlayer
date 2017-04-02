#pragma once

#include <MellowPlayer/UseCases/Services/INotificationsService.hpp>
#include "NotificationFactory.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IApplicationSettings)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILocalAlbumArtService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, INotificationPresenter)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PluginManager)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class NotificationService: public QObject, public UseCases::INotificationService {
    Q_OBJECT
public:
    NotificationService(UseCases::IPlayer& player, UseCases::ILocalAlbumArtService& localAlbumArtService,
                        UseCases::INotificationPresenter& presenter, UseCases::PluginManager& pluginManager,
                        UseCases::IApplicationSettings& applicationSettings);

    void initialize() override;
    bool display(const UseCases::Notification& notification) override;

public slots:
    void onCurrentSongChanged(UseCases::Song* song);
    void onPlaybackStatusChanged();
    void onCurrentSongUrlChanged();

private:
    void showNewSongNotification(UseCases::Song* song, const QString& localAlbumArtUrl);
    bool isPlaying() const;
    const QString getCurrentServiceName() const;
    const QString getCurrentServiceLogo() const;

    UseCases::ILogger& logger;
    UseCases::IPlayer& player;
    UseCases::ILocalAlbumArtService& localAlbumArtService;
    UseCases::INotificationPresenter& presenter;
    UseCases::PluginManager& pluginManager;
    UseCases::IApplicationSettings& applicationSettings;
    UseCases::Notification previousNotif;
    NotificationFactory notificationFactory;
};

END_MELLOWPLAYER_NAMESPACE
