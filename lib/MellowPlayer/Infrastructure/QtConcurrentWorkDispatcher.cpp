#include <QtConcurrent>
#include <QtCore/QThreadPool>
#include "QtConcurrentWorkDispatcher.hpp"

using namespace std;
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
USE_MELLOWPLAYER_NAMESPACE(UseCases)


void QtConcurrentWorkDispatcher::invoke(const function<void(void)>& workerFunction) {
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() {
        QMutexLocker mutexLocker(&mutex);
        workerFunction();
    });
}
