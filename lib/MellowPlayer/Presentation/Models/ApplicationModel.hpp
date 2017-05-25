#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>
#include <MellowPlayer/UseCases/Interfaces/IQtApplication.hpp>
#include "MellowPlayer/Presentation/Models/StreamingServices/StreamingServicesModel.hpp"

#define MELLOWPLAYER_APP_NAME "MellowPlayer3"

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ApplicationModel: public UseCases::IQtApplication {

public:
    ApplicationModel(int &argc, char **argv, const QString& appName=MELLOWPLAYER_APP_NAME);

    int run() override;
    Q_INVOKABLE void quit() override;
    Q_INVOKABLE void requestQuit() override;
    void registerToQml(QQmlApplicationEngine& applicationEngine);

private:
    QApplication qtApp;
    UseCases::ILogger& logger;
};

END_MELLOWPLAYER_NAMESPACE
