#pragma once

#include "IApplication.hpp"

namespace MellowPlayer::Infrastructure
{
    class ApplicationDecorator: public IApplication
    {
    public:
        ApplicationDecorator(IApplication& application);
        void initialize() override;
        int run() override;
        void quit() override;
        void restart() override;

        void restoreWindow() override;

    protected:
        IApplication& application_;
    };
}
