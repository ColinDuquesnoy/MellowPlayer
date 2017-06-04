#pragma once

#include <QMutex>
#include <MellowPlayer/Application/Utils/IWorkDispatcher.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class QtConcurrentWorkDispatcher: public Application::IWorkDispatcher {
public:
    void invoke(const std::function<void(void)>& workerFunction) override;

private:
    QMutex mutex;
};

END_MELLOWPLAYER_NAMESPACE

