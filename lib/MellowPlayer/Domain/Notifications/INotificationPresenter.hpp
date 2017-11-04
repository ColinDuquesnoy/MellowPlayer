#pragma once

namespace MellowPlayer::Domain
{
    struct Notification;

    class INotificationPresenter
    {
    public:
        virtual ~INotificationPresenter() = default;
        virtual void initialize() = 0;
        virtual bool display(const Domain::Notification& notification) = 0;
    };
}
