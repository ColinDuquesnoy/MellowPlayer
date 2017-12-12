#pragma once

#include <memory>
#include "IApplication.hpp"

namespace MellowPlayer::Infrastructure
{
    class ApplicationDecorator: public IApplication
    {
    public:
        explicit ApplicationDecorator(const std::shared_ptr<IApplication>& application);

        void initialize() override;
        int run() override;
        void quit() override;
        void restart() override;
        void restoreWindow() override;

    protected:
        std::shared_ptr<IApplication> application_;
    };
}
