#pragma once

#ifdef USE_LIBNOTIFY

#include <MellowPlayer/Application/Interfaces/INotificationPresenter.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)
struct _NotifyNotification;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class LibnotifyPresenter: public Application::INotificationPresenter {
public:
    LibnotifyPresenter(Application::IMainWindow& mainWindow);
    void initialize() override;
    bool display(const Entities::Notification& notification) override;

    static void onActionCallback();

private:
    Application::ILogger& logger;
    Application::IMainWindow& mainWindow;
    _NotifyNotification* previousNotification;
    static LibnotifyPresenter* instance;

};

END_MELLOWPLAYER_NAMESPACE

#endif
