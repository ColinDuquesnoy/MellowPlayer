#pragma once

#include <MellowPlayer/Domain/IWorkDispatcher.hpp>
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
        explicit LibnotifyPresenter(IMainWindow& mainWindow, Domain::IWorkDispatcher& workDispatcher);

        void initialize() override;
        bool display(const Notification& notification) override;

        static void onActionCallback();

    private:
        void checkSupportForActions();


        Domain::ILogger& logger_;
        IMainWindow& mainWindow_;
        Domain::IWorkDispatcher& _workDispatcher;
        _NotifyNotification* previousNotification_;
        bool actionsSupported_ = true;
        static LibnotifyPresenter* instance_;
    };
}
