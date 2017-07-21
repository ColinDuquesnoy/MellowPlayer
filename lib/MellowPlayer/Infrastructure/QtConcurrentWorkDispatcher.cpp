#include "QtConcurrentWorkDispatcher.hpp"
#include <QtConcurrent>
#include <QtCore/QThreadPool>

using namespace std;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Application;

QtConcurrentWorkDispatcher::QtConcurrentWorkDispatcher()
{
    connect(&timer, &QTimer::timeout, this, &QtConcurrentWorkDispatcher::onTimeout);
}

void QtConcurrentWorkDispatcher::invoke(const function<void(void)> &workerFunction)
{
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() {
        QMutexLocker mutexLocker(&mutex);
        workerFunction();
    });
}

void QtConcurrentWorkDispatcher::delayInvoke(int delayMilliseconds, const std::function<void(void)> &workerFunction)
{
    delayedWorkerFunction = workerFunction;
    timer.stop();
    timer.setInterval(delayMilliseconds);
    timer.start();
}

void QtConcurrentWorkDispatcher::onTimeout()
{
    invoke(delayedWorkerFunction);
}
