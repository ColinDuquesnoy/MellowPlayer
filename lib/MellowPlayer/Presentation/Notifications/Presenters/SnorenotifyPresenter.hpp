#pragma once

#ifdef USE_SNORENOTIFY

#include <MellowPlayer/UseCases/Interfaces/INotificationPresenter.hpp>
#include <libsnore/snore.h>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IMainWindow)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SnorenotifyPresenter: public QObject, public UseCases::INotificationPresenter {
    Q_OBJECT
public:
    SnorenotifyPresenter(UseCases::IMainWindow& mainWindow);
    void initialize() override;
    bool display(const Entities::Notification& notification) override;

private slots:
    void onActionInvoked(const Snore::Notification &notification);

private:
    UseCases::IMainWindow& mainWindow;
    UseCases::ILogger& logger;
    Snore::Application snoreApp;
    Snore::Notification oldNotification;
};

END_MELLOWPLAYER_NAMESPACE

#endif