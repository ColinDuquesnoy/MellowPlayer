#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>
#include <MellowPlayer/Application/Presentation/IQtApplication.hpp>
#include "MellowPlayer/Presentation/Models/StreamingServices/StreamingServicesModel.hpp"

#define MELLOWPLAYER_APP_NAME "MellowPlayer3"

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class QtApplicationModel: public Application::IQtApplication {

public:
    QtApplicationModel(int &argc, char **argv, const QString& appName=MELLOWPLAYER_APP_NAME);

    int run() override;
    Q_INVOKABLE void clearCache() const override;
    Q_INVOKABLE void clearCookies() const override;
    Q_INVOKABLE void restart() override;
    Q_INVOKABLE void requestQuit() override;
    Q_INVOKABLE void quit() override;

private:
    QApplication qtApp;
};

END_MELLOWPLAYER_NAMESPACE
