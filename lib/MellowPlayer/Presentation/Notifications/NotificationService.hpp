#pragma once

#include <MellowPlayer/Application/Interfaces/INotificationsService.hpp>
#include "NotificationFactory.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILocalAlbumArtService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, INotificationPresenter)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServicePluginService)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class NotificationService: public QObject, public Application::INotificationService {
    Q_OBJECT
public:
    NotificationService(Application::IPlayer& player, Application::ILocalAlbumArtService& localAlbumArtService,
                        Application::INotificationPresenter& presenter, Application::StreamingServicePluginService& pluginService,
                        Application::Settings& settings);

    void initialize() override;
    bool display(const Entities::Notification& notification) override;

public slots:
    void onCurrentSongChanged(Entities::Song* song);
    void onPlaybackStatusChanged();
    void onCurrentSongUrlChanged();

private:
    void showSongNotification(Entities::Song* song, const QString& localAlbumArtUrl);
    bool isPlaying() const;
    const QString getCurrentServiceName() const;
    const QString getCurrentServiceLogo() const;
    bool isNotificationTypeEnabled(Entities::NotificationType type) const;

    Application::ILogger& logger;
    Application::IPlayer& player;
    Application::ILocalAlbumArtService& localAlbumArtService;
    Application::INotificationPresenter& presenter;
    Application::StreamingServicePluginService& pluginService;
    Application::Settings& settings;
    Entities::Notification previousNotif;
    NotificationFactory notificationFactory;
    QString previousSongId;
};

END_MELLOWPLAYER_NAMESPACE
