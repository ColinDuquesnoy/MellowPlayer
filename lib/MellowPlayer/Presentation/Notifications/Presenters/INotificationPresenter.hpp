#pragma once

namespace MellowPlayer::Presentation
{
    struct Notification;

    class INotificationPresenter
    {
    public:
        virtual ~INotificationPresenter() = default;
        virtual void initialize() = 0;
        virtual bool display(const Notification& notification) = 0;
    };
}
