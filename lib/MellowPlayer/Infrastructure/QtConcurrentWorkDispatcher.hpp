#pragma once

#include <QMutex>
#include <MellowPlayer/UseCases/IWorkDispatcher.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class QtConcurrentWorkDispatcher: public UseCases::IWorkDispatcher {
public:
    void invoke(const std::function<void(void)>& workerFunction) override;

private:
    QMutex mutex;
};

END_MELLOWPLAYER_NAMESPACE

