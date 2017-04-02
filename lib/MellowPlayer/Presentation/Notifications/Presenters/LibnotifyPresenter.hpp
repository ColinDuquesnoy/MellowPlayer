#pragma once

#ifdef USE_LIBNOTIFY

#include <MellowPlayer/UseCases/Notifications/INotificationPresenter.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IMainWindow)
struct _NotifyNotification;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class LibnotifyPresenter: public UseCases::INotificationPresenter {
public:
    LibnotifyPresenter(UseCases::IMainWindow& mainWindow);
    void initialize() override;
    bool display(const UseCases::Notification& notification) override;

    static void onActionCallback();

private:
    UseCases::ILogger& logger;
    UseCases::IMainWindow& mainWindow;
    _NotifyNotification* previousNotification;
    static LibnotifyPresenter* instance;

};

END_MELLOWPLAYER_NAMESPACE

#endif
