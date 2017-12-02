#include "SingleInstance.hpp"
#include "QtApplication.hpp"
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

const QString SingleInstance::playPauseAction_ = "play-pause";
const QString SingleInstance::nextAction_ = "next";
const QString SingleInstance::previousAction_ = "previous";
const QString SingleInstance::restoreWindowAction_ = "restore-window";
const QString SingleInstance::toggleFavoriteAction_ = "toggle-favorite";

SingleInstance::SingleInstance(IApplication& application,
                               IQtApplication& qtApplication,
                               IPlayer& currentPlayer,
                               ICommandLineArguments& commandLineArguments,
                               IFactory<ILocalServer, QString>& localServerFactory,
                               IFactory<ILocalSocket>& localSocketFactory)
        : ApplicationDecorator(application),
          logger_(LoggingManager::logger("SingleInstance")),
          qtApplication_(qtApplication),
          currentPlayer_(currentPlayer),
          commandLineArguments_(commandLineArguments),
          localServerFactory_(localServerFactory),
          localSocketFactory_(localSocketFactory),
          lockFile_(QDir::tempPath() + QDir::separator() + qApp->applicationName() + ".lock"),
          isPrimary_(false)
{
    lockFile_.setStaleLockTime(0);
}

void SingleInstance::initialize()
{
    if (lockFile_.tryLock(100)) {
        LOG_DEBUG(logger_, "Initializing primary application");
        isPrimary_ = true;
        application_.initialize();
    }
}

int SingleInstance::run()
{
    return isPrimary_ ? runPrimaryApplication() : runSecondaryApplication();
}

bool SingleInstance::isPrimary() const
{
    return isPrimary_;
}

int SingleInstance::runPrimaryApplication()
{
    LOG_DEBUG(logger_, "Running primary application");
    
    localServer_ = localServerFactory_.create(qApp->applicationName());
    connect(localServer_.get(), &ILocalServer::newConnection, this, &SingleInstance::onSecondaryApplicationConnection);
    localServer_->listen();

    return application_.run();
}

void SingleInstance::onSecondaryApplicationConnection()
{
    LOG_DEBUG(logger_, "Another application was started, showing this one instead");
    localSocket_ = localServer_->nextPendingConnection();    
    connect(localSocket_.get(), &ILocalSocket::readyRead, this, &SingleInstance::onSecondaryApplicationActionRequest);
}

void SingleInstance::onSecondaryApplicationActionRequest()
{
    QString action = QString(localSocket_->readAll()).split("\n")[0];
    LOG_DEBUG(logger_, "Secondary application request: " << action);

    if (action == playPauseAction_)
        currentPlayer_.togglePlayPause();
    else if (action == nextAction_)
        currentPlayer_.next();
    else if (action == previousAction_)
        currentPlayer_.previous();
    else if (action == toggleFavoriteAction_)
        currentPlayer_.toggleFavoriteSong();
    else
        application_.restoreWindow();
}

int SingleInstance::runSecondaryApplication()
{
    LOG_DEBUG(logger_, "Running secondary application");
    
    localSocket_ = localSocketFactory_.create();
    localSocket_->connectToServer(qApp->applicationName(), QIODevice::WriteOnly);
    connect(localSocket_.get(), &ILocalSocket::connected, this, &SingleInstance::onConnectedToPrimaryApplication);
    connect(localSocket_.get(), &ILocalSocket::error, this, &SingleInstance::onConnectionErrorWithPrimaryApplication);

    return qtApplication_.exec();
}

void SingleInstance::onConnectedToPrimaryApplication()
{
    LOG_INFO(logger_, "connection with the primary application succeeded, transmitting command line arguments "
            "and quitting...");
    QString action = requestedAcion();
    localSocket_->write(action + "\n");
    qtApplication_.exit(1);
}

void SingleInstance::onConnectionErrorWithPrimaryApplication()
{
    LOG_INFO(logger_, "could not connect to the primary application, quitting...");
    qtApplication_.exit(2);
}

QString SingleInstance::requestedAcion() const
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
