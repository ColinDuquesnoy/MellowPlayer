#include "DeprecatedSingleInstanceApplication.hpp"
#include "IDeprecatedApplication.hpp"
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <QCoreApplication>
#include <QFile>
#include <QTimer>
#ifdef Q_OS_UNIX
#include <signal.h>
#endif

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

const QString DeprecatedSingleInstanceApplication::playPauseAction_ = "play-pause";
const QString DeprecatedSingleInstanceApplication::nextAction_ = "next";
const QString DeprecatedSingleInstanceApplication::previousAction_ = "previous";
const QString DeprecatedSingleInstanceApplication::restoreWindowAction_ = "restore-window";
const QString DeprecatedSingleInstanceApplication::toggleFavoriteAction_ = "toggle-favorite";

DeprecatedSingleInstanceApplication::DeprecatedSingleInstanceApplication(IDeprecatedApplication& application,
                                                                         ICommandLineArguments& commandLineArguments,
                                                                         IPlayer& currentPlayer)
        : logger_(LoggingManager::logger("SingleInstanceApplication")),
          application_(application),
          commandLineArguments_(commandLineArguments),
          currentPlayer_(currentPlayer)
{
    connect(&localSocket_, &QLocalSocket::connected, this, &DeprecatedSingleInstanceApplication::onSocketConnected);
    connect(&localSocket_, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onSocketError()));
    connect(&localServer_, &QLocalServer::newConnection, this, &DeprecatedSingleInstanceApplication::onNewConnection);
}

int DeprecatedSingleInstanceApplication::run()
{
    LOG_TRACE(logger_, "run");
    LOG_DEBUG(logger_, "starting, connecting to local server");
    localSocket_.connectToServer(qApp->applicationName(), QIODevice::WriteOnly);
    auto retCode = application_.run();
    localSocket_.disconnectFromServer();
    localServer_.close();
    return retCode;
}

void DeprecatedSingleInstanceApplication::onSocketConnected()
{
    LOG_INFO(logger_, "another instance is already running, quitting");
    QString action = requestedAcion();
    localSocket_.write(QString(action + "\n").toLocal8Bit());
    QTimer::singleShot(100, this, &DeprecatedSingleInstanceApplication::quit);
}

void DeprecatedSingleInstanceApplication::onSocketError()
{
    LOG_DEBUG(logger_, "initializaing");
    localServer_.listen(qApp->applicationName());
    connectSignalHandlers();
    application_.initialize();
}

void DeprecatedSingleInstanceApplication::onNewConnection()
{
    LOG_DEBUG(logger_, "another instance was started, showing this instance instead");
    QLocalSocket* socket = localServer_.nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, &DeprecatedSingleInstanceApplication::onReadyRead);
}

void DeprecatedSingleInstanceApplication::connectSignalHandlers()
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

void DeprecatedSingleInstanceApplication::quit()
{
    LOG_TRACE(logger_, "quit");
    application_.quit();
}

QString DeprecatedSingleInstanceApplication::requestedAcion() const
{
    if (commandLineArguments_.playPauseRequested())
        return playPauseAction_;
    else if (commandLineArguments_.nextRequested())
        return nextAction_;
    else if (commandLineArguments_.previousRequested())
        return previousAction_;
    else if (commandLineArguments_.toggleFavoriteRequested())
        return toggleFavoriteAction_;
    return restoreWindowAction_;
}

void DeprecatedSingleInstanceApplication::onReadyRead()
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
