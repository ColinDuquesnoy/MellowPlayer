#include "SingleInstanceApplication.hpp"
#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <QCoreApplication>
#include <QFile>
#include <QTimer>
#ifdef Q_OS_UNIX
#include <signal.h>
#include <unistd.h>
#endif

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

const QString SingleInstanceApplication::playPauseAction = "play-pause";
const QString SingleInstanceApplication::nextAction = "next";
const QString SingleInstanceApplication::previousAction = "previous";
const QString SingleInstanceApplication::restoreWindowAction = "restore-window";

SingleInstanceApplication::SingleInstanceApplication(IApplication &application, ICommandLineParser &commandLineParser,
                                                     IPlayer &currentPlayer)
        : logger(LoggingManager::instance().getLogger("SingleInstanceApplication")),
          application(application),
          commandLineParser(commandLineParser),
          currentPlayer(currentPlayer)
{
    connect(&localSocket, &QLocalSocket::connected, this, &SingleInstanceApplication::onSocketConnected);
    connect(&localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onSocketError()));
    connect(&localServer, &QLocalServer::newConnection, this, &SingleInstanceApplication::onNewConnection);
}

int SingleInstanceApplication::run()
{
    LOG_TRACE(logger, "run");
    LOG_DEBUG(logger, "starting, connecting to local server");
    localSocket.connectToServer(qApp->applicationName(), QIODevice::WriteOnly);
    auto retCode = application.run();
    localSocket.disconnectFromServer();
    localServer.close();
    return retCode;
}

void SingleInstanceApplication::onSocketConnected()
{
    LOG_INFO(logger, "another instance is already running, quitting");
    QString action = getRequestedAcion();
    localSocket.write(QString(action + "\n").toLocal8Bit());
    QTimer::singleShot(100, this, &SingleInstanceApplication::quit);
}

void SingleInstanceApplication::onSocketError()
{
    LOG_DEBUG(logger, "initializaing");
    localServer.listen(qApp->applicationName());
    connectSignalHandlers();
    application.initialize();
}

void SingleInstanceApplication::onNewConnection()
{
    LOG_DEBUG(logger, "another instance was started, showing this instance instead");
    QLocalSocket *socket = localServer.nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, &SingleInstanceApplication::onReadyRead);
}

void SingleInstanceApplication::connectSignalHandlers()
{
#ifdef Q_OS_UNIX
    auto handler = [](int sig) -> void {
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

void SingleInstanceApplication::quit()
{
    LOG_TRACE(logger, "quit");
    application.quit();
}

QString SingleInstanceApplication::getRequestedAcion() const
{
    if (commandLineParser.isPlayPauseRequested())
        return playPauseAction;
    else if (commandLineParser.isNextRequested())
        return nextAction;
    else if (commandLineParser.isPreviousRequested())
        return previousAction;
    return restoreWindowAction;
}

void SingleInstanceApplication::onReadyRead()
{
    QLocalSocket *socket = static_cast<QLocalSocket *>(sender());
    QStringList actions = QString(socket->readAll()).split("\n");
    for (const auto &a : actions) {
        if (a == playPauseAction)
            currentPlayer.togglePlayPause();
        else if (a == nextAction)
            currentPlayer.next();
        else if (a == previousAction)
            currentPlayer.previous();
        else
            application.restoreWindow();
    }
}
