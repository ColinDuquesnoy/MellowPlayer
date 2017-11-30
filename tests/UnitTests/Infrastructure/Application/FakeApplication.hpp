#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <gmock/gmock.h>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeApplication: public IApplication
    {
    public:
        void initialize() override;
        int run() override;
        void quit() override;
        void restart() override;
        void restoreWindow() override;

        int returnCode = 0;
        bool isInitialized = false;
        bool isRunning = false;
        bool quitRequested = false;
        bool restartRequested = false;
        bool restoreWindowRequested = false;
    };
}
