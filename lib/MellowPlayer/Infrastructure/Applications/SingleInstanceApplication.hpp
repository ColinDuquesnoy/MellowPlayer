#pragma once

#include <QObject>
#include <QLocalSocket>
#include <QLocalServer>
#include <MellowPlayer/Logging.hpp>
#include "IApplication.hpp"

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
    Logging::ILogger& logger;
    IApplication& application;
    QLocalSocket localSocket;
    QLocalServer localServer;
};

END_MELLOWPLAYER_NAMESPACE
