#include <QTimer>
#include <QFile>
#include <QCoreApplication>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "SingleInstanceApplication.hpp"
#ifdef Q_OS_UNIX
#include <signal.h>
#include <unistd.h>
#endif

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)

SingleInstanceApplication::SingleInstanceApplication(IApplication& application):
        logger(LoggingManager::instance().getLogger("SingleInstanceApplication")),
    application(application) {
    connect(&localSocket, &QLocalSocket::connected, this, &SingleInstanceApplication::onSocketConnected);
    connect(&localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onSocketError()));
    connect(&localServer, &QLocalServer::newConnection, this, &SingleInstanceApplication::onNewConnection);
}

int SingleInstanceApplication::run() {
    LOG_TRACE(logger, "run");
    LOG_DEBUG(logger, "starting, connecting to local server");
    localSocket.connectToServer(qApp->applicationName(), QIODevice::WriteOnly);
    return application.run();
}

void SingleInstanceApplication::onSocketConnected() {
    LOG_INFO(logger, "another instance is already running, quitting");
    QTimer::singleShot(100, this, &SingleInstanceApplication::quit);
}

void SingleInstanceApplication::onSocketError() {
    LOG_DEBUG(logger, "initializaing");
    localServer.listen(qApp->applicationName());
    connectSignalHandlers();
    application.initialize();
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
        QFile::remove("/tmp/" + qApp->applicationName());
        QCoreApplication::quit();
    };
    QList<int> unix_signals = {SIGKILL, SIGTERM, SIGQUIT, SIGINT};
        foreach (int sig, unix_signals) {
            signal(sig, handler);
        }
#endif
}

void SingleInstanceApplication::quit() {
    LOG_TRACE(logger, "quit");
    application.quit();
}
