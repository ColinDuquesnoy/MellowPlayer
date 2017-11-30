#pragma once

#include <MellowPlayer/Domain/Notifications/INotificationPresenter.hpp>

struct _NotifyNotification;

namespace MellowPlayer::Domain
{
    class ILogger;
    class IDeprecatedMainWindow;
    struct Notification;
}

namespace MellowPlayer::Presentation
{
    class LibnotifyPresenter : public Domain::INotificationPresenter
    {
    public:
        explicit LibnotifyPresenter(Domain::IDeprecatedMainWindow& mainWindow);
        void initialize() override;
        bool display(const Domain::Notification& notification) override;

        static void onActionCallback();

    private:
        void checkSupportForActions();

        Domain::ILogger& logger_;
        Domain::IDeprecatedMainWindow& mainWindow_;
        _NotifyNotification* previousNotification_;
        bool actionsSupported_ = true;
        static LibnotifyPresenter* instance_;
    };
}
