#pragma once

#include <MellowPlayer/UseCases/IWorkDispatcher.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class QtConcurrentWorkDispatcher: public UseCases::IWorkDispatcher {
public:
    void execute(const std::function<void(void)>& workerFunction) override;
};

END_MELLOWPLAYER_NAMESPACE

