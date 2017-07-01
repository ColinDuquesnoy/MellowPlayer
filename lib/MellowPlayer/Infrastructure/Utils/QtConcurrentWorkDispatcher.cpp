#include <QtConcurrent>
#include <QtCore/QThreadPool>
#include "QtConcurrentWorkDispatcher.hpp"

using namespace std;
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
USING_MELLOWPLAYER_NAMESPACE(Application)


void QtConcurrentWorkDispatcher::invoke(const function<void(void)>& workerFunction) {
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() {
        QMutexLocker mutexLocker(&mutex);
        workerFunction();
    });
}
