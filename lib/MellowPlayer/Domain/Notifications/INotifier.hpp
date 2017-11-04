#pragma once

namespace MellowPlayer::Domain
{
    struct Notification;

    class INotifier
    {
    public:
        virtual ~INotifier() = default;
        virtual void initialize() = 0;
        virtual bool display(const Domain::Notification& notification) = 0;
    };
}