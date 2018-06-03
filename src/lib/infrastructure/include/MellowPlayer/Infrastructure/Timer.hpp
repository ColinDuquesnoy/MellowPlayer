#pragma once

#include <MellowPlayer/Infrastructure/ITimer.hpp>
#include <QTimer>

namespace MellowPlayer::Infrastructure
{
    class Timer: public QObject, public ITimer
    {
    public:
        void start(int timeout, std::function<void ()> callback) override;
        void stop() override;

    private:
        QTimer _timer;
        std::function<void()> _callback;

    };
}
