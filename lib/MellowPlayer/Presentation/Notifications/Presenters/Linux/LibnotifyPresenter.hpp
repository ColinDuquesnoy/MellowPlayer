#pragma once

#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>

struct _NotifyNotification;

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Presentation
{
    class IMainWindow;
    struct Notification;

    class LibnotifyPresenter : public INotificationPresenter
    {
    public:
        explicit LibnotifyPresenter(IMainWindow& mainWindow);

        void initialize() override;
        bool display(const Notification& notification) override;

        static void onActionCallback();

    private:
        void checkSupportForActions();

        Domain::ILogger& logger_;
        IMainWindow& mainWindow_;
        _NotifyNotification* previousNotification_;
        bool actionsSupported_ = true;
        static LibnotifyPresenter* instance_;
    };
}
