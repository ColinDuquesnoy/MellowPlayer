#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>

namespace MellowPlayer::Infrastructure
{
    class IQtApplication;

    class Application : public Infrastructure::IApplication
    {
        Q_OBJECT
    public:
        Application(IQtApplication& qtApplication);

        void initialize() override;
        int run() override;
        void quit() override;
        void restart() override;
        void restoreWindow() override;

    private:
        Infrastructure::IQtApplication& qtApp_;
        bool restartRequested_;
    };
}

