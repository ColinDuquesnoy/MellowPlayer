#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>
#include <MellowPlayer/Application/Presentation/IQtApplication.hpp>
#include "MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp"

#define MELLOWPLAYER_APP_NAME "MellowPlayer"

namespace MellowPlayer::Application {

    class ILogger;

}

namespace MellowPlayer::Presentation {

    class ApplicationViewModel: public Application::IQtApplication {
    public:
        ApplicationViewModel(int &argc, char **argv, const QString& appName=MELLOWPLAYER_APP_NAME);

        int run() override;
        Q_INVOKABLE void clearCache() const override;
        Q_INVOKABLE void clearCookies() const override;
        Q_INVOKABLE void restart() override;
        Q_INVOKABLE void requestQuit() override;
        Q_INVOKABLE void quit() override;

        void setAutoQuitDelay(int delay);

        bool restartRequested() const override { return restartRequested_; }

    private:
        QApplication qtApp;
        bool restartRequested_ = false;
    };

}
