#include <MellowPlayer/Infrastructure/Timer.hpp>

using namespace MellowPlayer::Infrastructure;


void Timer::start(int timeout, std::function<void ()> callback)
{
    _timer.setInterval(timeout);
    connect(&_timer, &QTimer::timeout, [=](){ callback(); });
    _timer.start();
}

void Timer::stop()
{
    _timer.stop();
}

