#pragma once

#include <MellowPlayer/Domain/Notifications/INotificationPresenter.hpp>

struct _NotifyNotification;

namespace MellowPlayer::Domain
{
    class ILogger;
    class IMainWindow;
    struct Notification;
}

namespace MellowPlayer::Presentation
{
    class LibnotifyPresenter : public Domain::INotificationPresenter
    {
    public:
        explicit LibnotifyPresenter(Domain::IMainWindow& mainWindow);
        void initialize() override;
        bool display(const Domain::Notification& notification) override;

        static void onActionCallback();

    private:
        Domain::ILogger& logger_;
        Domain::IMainWindow& mainWindow_;
        _NotifyNotification* previousNotification_;
        static LibnotifyPresenter* instance_;
    };
}
