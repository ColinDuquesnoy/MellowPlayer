#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <QApplication>
#include <QTranslator>

namespace MellowPlayer::Infrastructure
{
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

