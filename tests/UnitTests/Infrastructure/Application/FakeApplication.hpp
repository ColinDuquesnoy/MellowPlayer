#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeApplication: public IApplication
    {
    public:
        void initialize() override
        {
            isInitialized = true;
            emit initialized();
        }

        int run() override
        {
            isRunning = true;
            return returnCode;
        }

        void quit() override
        {
            quitRequested = true;
        }

        void restart() override
        {
            restartRequested = true;
        }

        void restoreWindow() override
        {
            restoreWindowRequested = true;
            emit restoreWindowRequest();
        }

        int returnCode = 0;
        bool isInitialized = false;
        bool isRunning = false;
        bool quitRequested = false;
        bool restartRequested = false;
        bool restoreWindowRequested = false;
    };
}
