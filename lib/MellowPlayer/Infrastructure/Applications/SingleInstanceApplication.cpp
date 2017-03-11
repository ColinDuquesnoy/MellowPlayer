#include <QTimer>
#include <QFile>
#include <QCoreApplication>
#include "SingleInstanceApplication.hpp"
#ifdef Q_OS_UNIX
#include <signal.h>
#include <unistd.h>
#endif

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

SingleInstanceApplication::SingleInstanceApplication(IApplication& application):
        logger(LoggingManager::instance().getLogger("SingleInstanceApplication")),
    application(application) {
    connect(&localSocket, &QLocalSocket::connected, this, &SingleInstanceApplication::onSocketConnected);
    connect(&localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onSocketError()));
    connect(&localServer, &QLocalServer::newConnection, this, &SingleInstanceApplication::onNewConnection);
}

int SingleInstanceApplication::run() {
    LOG_DEBUG(logger, "connecting to locale server");
    localSocket.connectToServer("MellowPlayer3", QIODevice::WriteOnly);
    return application.run();
}

void SingleInstanceApplication::onSocketConnected() {
    LOG_DEBUG(logger, "Another instance is already running, quitting");
    QTimer::singleShot(100, this, &SingleInstanceApplication::quit);
}

void SingleInstanceApplication::onSocketError() {
    localServer.listen("MellowPlayer3");
    connectSignalHandlers();
    application.initialize();
    application.restoreWindow();
}

void SingleInstanceApplication::onNewConnection() {
    LOG_DEBUG(logger, "another instance was started, showing this instance instead");
    application.restoreWindow();
}

void SingleInstanceApplication::connectSignalHandlers()
{
#ifdef Q_OS_UNIX
    auto handler = [](int sig) ->void {
        printf("\nquit the application (user request signal = %d).\n", sig);
        QFile::remove("/tmp/MellowPlayer");
        QCoreApplication::quit();
    };
    QList<int> unix_signals = {SIGKILL, SIGTERM, SIGQUIT, SIGINT};
        foreach (int sig, unix_signals) {
            signal(sig, handler);
        }
#endif
}

void SingleInstanceApplication::quit() {
    application.quit();
}
