#pragma once

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <MellowPlayer/Application/Utils/IWorkDispatcher.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class QtConcurrentWorkDispatcher: public QObject, public Application::IWorkDispatcher {
    Q_OBJECT
public:
    QtConcurrentWorkDispatcher();
    void invoke(const std::function<void(void)>& workerFunction) override;
    void delayInvoke(int delayMilliseconds, const std::function<void(void)>& workerFunction) override;

private slots:
    void onTimeout();

private:
    QMutex mutex;
    QTimer timer;
    std::function<void(void)> delayedWorkerFunction;
};

END_MELLOWPLAYER_NAMESPACE
