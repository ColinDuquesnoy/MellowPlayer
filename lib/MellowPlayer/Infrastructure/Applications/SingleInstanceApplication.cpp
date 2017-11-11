#include "SingleInstanceApplication.hpp"
#include "IDeprecatedApplication.hpp"
#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <MellowPlayer/Application/Logging/ILogger.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <QCoreApplication>
#include <QFile>
#include <QTimer>
#ifdef Q_OS_UNIX
#include <signal.h>
#endif

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

const QString SingleInstanceApplication::playPauseAction_ = "play-pause";
const QString SingleInstanceApplication::nextAction_ = "next";
const QString SingleInstanceApplication::previousAction_ = "previous";
const QString SingleInstanceApplication::restoreWindowAction_ = "restore-window";
const QString SingleInstanceApplication::toggleFavoriteAction_ = "toggle-favorite";

SingleInstanceApplication::SingleInstanceApplication(IDeprecatedApplication& application, ICommandLineParser& commandLineParser, IPlayer& currentPlayer)
        : logger_(LoggingManager::logger("SingleInstanceApplication")),
          application_(application),
          commandLineParser_(commandLineParser),
          currentPlayer_(currentPlayer)
{
    connect(&localSocket_, &QLocalSocket::connected, this, &SingleInstanceApplication::onSocketConnected);
    connect(&localSocket_, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onSocketError()));
    connect(&localServer_, &QLocalServer::newConnection, this, &SingleInstanceApplication::onNewConnection);
}

int SingleInstanceApplication::run()
{
    LOG_TRACE(logger_, "run");
    LOG_DEBUG(logger_, "starting, connecting to local server");
    localSocket_.connectToServer(qApp->applicationName(), QIODevice::WriteOnly);
    auto retCode = application_.run();
    localSocket_.disconnectFromServer();
    localServer_.close();
    return retCode;
}

void SingleInstanceApplication::onSocketConnected()
{
    LOG_INFO(logger_, "another instance is already running, quitting");
    QString action = requestedAcion();
    localSocket_.write(QString(action + "\n").toLocal8Bit());
    QTimer::singleShot(100, this, &SingleInstanceApplication::quit);
}

void SingleInstanceApplication::onSocketError()
{
    LOG_DEBUG(logger_, "initializaing");
    localServer_.listen(qApp->applicationName());
    connectSignalHandlers();
    application_.initialize();
}

void SingleInstanceApplication::onNewConnection()
{
    LOG_DEBUG(logger_, "another instance was started, showing this instance instead");
    QLocalSocket* socket = localServer_.nextPendingConnection();
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
    LOG_TRACE(logger_, "quit");
    application_.quit();
}

QString SingleInstanceApplication::requestedAcion() const
{
    if (commandLineParser_.playPauseRequested())
        return playPauseAction_;
    else if (commandLineParser_.nextRequested())
        return nextAction_;
    else if (commandLineParser_.previousRequested())
        return previousAction_;
    else if (commandLineParser_.toggleFavoriteRequested())
        return toggleFavoriteAction_;
    return restoreWindowAction_;
}

void SingleInstanceApplication::onReadyRead()
{
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    QStringList actions = QString(socket->readAll()).split("\n");
    for (const auto& a : actions) {
        if (a == playPauseAction_)
            currentPlayer_.togglePlayPause();
        else if (a == nextAction_)
            currentPlayer_.next();
        else if (a == previousAction_)
            currentPlayer_.previous();
        else if (a == toggleFavoriteAction_)
            currentPlayer_.toggleFavoriteSong();
        else
            application_.restoreWindow();
    }
}
