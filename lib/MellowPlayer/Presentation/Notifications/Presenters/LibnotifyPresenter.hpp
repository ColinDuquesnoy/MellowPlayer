#pragma once

#include <MellowPlayer/Application/Notifications/INotificationPresenter.hpp>

struct _NotifyNotification;
namespace MellowPlayer::Application {

    class ILogger;
    class IMainWindow;

}

namespace MellowPlayer::Presentation {

    class LibnotifyPresenter: public Application::INotificationPresenter {
    public:
        LibnotifyPresenter(Application::IMainWindow& mainWindow);
        void initialize() override;
        bool display(const Application::Notification& notification) override;

        static void onActionCallback();

    private:
        Application::ILogger& logger;
        Application::IMainWindow& mainWindow;
        _NotifyNotification* previousNotification;
        static LibnotifyPresenter* instance;

    };

}
