#pragma once

namespace MellowPlayer::Infrastructure
{
    class IApplication {
    public:
        virtual ~IApplication() = default;

        virtual void initialize() = 0;
        virtual void run() = 0;
        virtual void quit() = 0;
        virtual void restart() = 0;

        virtual void restoreWindow() = 0;
        virtual void buildInfo() = 0;
    };
}