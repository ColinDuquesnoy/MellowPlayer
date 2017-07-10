#pragma once

namespace MellowPlayer::Application {

    struct Notification;

    class INotifier {
    public:
        virtual ~INotifier() = default;
        virtual void initialize() = 0;
        virtual bool display(const Application::Notification& notification) = 0;
    };

}