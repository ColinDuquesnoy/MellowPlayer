#pragma once

#include <MellowPlayer/Application/IWorkDispatcher.hpp>
#include <QMutex>
#include <QObject>
#include <QTimer>

namespace MellowPlayer::Infrastructure
{
    class QtConcurrentWorkDispatcher : public QObject, public Application::IWorkDispatcher
    {
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
}
