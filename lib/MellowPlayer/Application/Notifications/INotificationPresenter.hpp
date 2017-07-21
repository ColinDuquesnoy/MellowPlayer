#pragma once

namespace MellowPlayer::Application
{
    struct Notification;

    class INotificationPresenter
    {
    public:
        virtual ~INotificationPresenter() = default;
        virtual void initialize() = 0;
        virtual bool display(const Application::Notification &notification) = 0;
    };
}
