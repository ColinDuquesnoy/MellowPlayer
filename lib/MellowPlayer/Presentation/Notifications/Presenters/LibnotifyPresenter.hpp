#pragma once

#include <MellowPlayer/Application/Notifications/INotificationPresenter.hpp>

struct _NotifyNotification;

namespace MellowPlayer::Application
{
    class ILogger;
    class IMainWindow;
}

namespace MellowPlayer::Presentation
{
    class LibnotifyPresenter : public Application::INotificationPresenter
    {
    public:
        explicit LibnotifyPresenter(Application::IMainWindow& mainWindow);
        void initialize() override;
        bool display(const Application::Notification& notification) override;

        static void onActionCallback();

    private:
        Application::ILogger& logger_;
        Application::IMainWindow& mainWindow_;
        _NotifyNotification* previousNotification_;
        static LibnotifyPresenter* instance_;
    };
}
