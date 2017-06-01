#pragma once

#include <MellowPlayer/Application/IWorkDispatcher.hpp>

class FakeWorkDispatcher: public MellowPlayer::Application::IWorkDispatcher {
public:
    void invoke(const std::function<void(void)>& workerFunction) override {
        workerFunction();
    };
};
