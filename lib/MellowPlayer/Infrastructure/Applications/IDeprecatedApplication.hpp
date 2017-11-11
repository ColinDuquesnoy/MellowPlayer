#pragma once

namespace MellowPlayer::Infrastructure
{
    class IDeprecatedApplication
    {
    public:
        virtual ~IDeprecatedApplication() = default;
        virtual void initialize() = 0;
        virtual void restoreWindow() = 0;
        virtual int run() = 0;
        virtual void quit() = 0;
    };
}
