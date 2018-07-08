#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <QtConcurrent>

using namespace std;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Domain;

QtConcurrentWorkDispatcher::QtConcurrentWorkDispatcher()
{
    connect(&timer_, &QTimer::timeout, this, &QtConcurrentWorkDispatcher::onTimeout);
}

void QtConcurrentWorkDispatcher::invoke(const function<void(void)>& workerFunction)
{
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() {
        QMutexLocker mutexLocker(&mutex_);
        workerFunction();
    });
}

void QtConcurrentWorkDispatcher::delayInvoke(int delayMilliseconds, const std::function<void(void)>& workerFunction)
{
    delayedWorkerFunction = workerFunction;
    timer_.stop();
    timer_.setInterval(delayMilliseconds);
    timer_.start();
}

void QtConcurrentWorkDispatcher::onTimeout()
{
    invoke(delayedWorkerFunction);
}
