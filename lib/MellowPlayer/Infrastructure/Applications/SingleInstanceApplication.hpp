#pragma once

#include <QObject>
#include <QLocalSocket>
#include <QLocalServer>
#include "IApplication.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SingleInstanceApplication : public QObject {
    Q_OBJECT
public:
    SingleInstanceApplication(IApplication& application);

    int run();

private slots:
    void onSocketConnected();
    void onSocketError();
    void onNewConnection();
    void connectSignalHandlers();
    void quit();

private:
    Application::ILogger& logger;
    IApplication& application;
    QLocalSocket localSocket;
    QLocalServer localServer;
};

END_MELLOWPLAYER_NAMESPACE
