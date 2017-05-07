#pragma once

#include <MellowPlayer/UseCases/IWorkDispatcher.hpp>

class FakeWorkDispatcher: public MellowPlayer::UseCases::IWorkDispatcher {
public:
    void invoke(const std::function<void(void)>& workerFunction) override {
        workerFunction();
    };
};
