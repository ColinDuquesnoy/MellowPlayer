#include <MellowPlayer/Infrastructure/Application/SingleInstance.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <QtCore/QDir>
#include <QtCore/QTimer>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

const QString SingleInstance::playPauseAction_ = "play-pause";
const QString SingleInstance::nextAction_ = "next";
const QString SingleInstance::previousAction_ = "previous";
const QString SingleInstance::restoreWindowAction_ = "restore-window";
const QString SingleInstance::toggleFavoriteAction_ = "toggle-favorite";

SingleInstance::SingleInstance(const std::shared_ptr<IApplication>& application,
                               IQtApplication& qtApplication,
                               IPlayer& currentPlayer,
                               ICommandLineArguments& commandLineArguments,
                               IFactory<ILocalServer, QString>& localServerFactory,
                               IFactory<ILocalSocket>& localSocketFactory)
        : ApplicationDecorator(application),
          logger_(Loggers::logger("SingleInstance")),
          qtApplication_(qtApplication),
          currentPlayer_(currentPlayer),
          commandLineArguments_(commandLineArguments),
          localServerFactory_(localServerFactory),
          localSocketFactory_(localSocketFactory),
          lockFilePath_(QDir::tempPath() + QDir::separator() + qApp->applicationName() + ".lock"),
          lockFile_(lockFilePath_),
          isPrimary_(false)
{
    lockFile_.setStaleLockTime(0);
}

SingleInstance::~SingleInstance() = default;

void SingleInstance::initialize()
{
    LOG_INFO(logger_, "lock file: " << lockFilePath_)
    if (lockFile_.tryLock(100)) {
        LOG_DEBUG(logger_, "Initializing primary application");
        isPrimary_ = true;
        ApplicationDecorator::initialize();
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
    connect(localServer_.get(), &ILocalServer::newConnection, this, &SingleInstance::onSecondaryApplicationConnected);
    localServer_->listen();

    connect(&pollStateTimer_, &QTimer::timeout, this, &SingleInstance::pollState);
    pollStateTimer_.setInterval(1000);
    pollStateTimer_.start();

    auto retCode = ApplicationDecorator::run();
    localServer_->close();
    lockFile_.unlock();
    return retCode;
}

void SingleInstance::onSecondaryApplicationConnected()
{
    LOG_INFO(logger_, "Another application was started, showing this one instead");
    localSocket_ = localServer_->nextPendingConnection();    
    connect(localSocket_.get(), &ILocalSocket::readyRead, this, &SingleInstance::onSecondaryApplicationActionRequest);
}

void SingleInstance::onSecondaryApplicationActionRequest()
{
    QString action = QString(localSocket_->readAll()).split("\n")[0];
    LOG_INFO(logger_, "Secondary application request: " << action);

    if (action == playPauseAction_)
        currentPlayer_.togglePlayPause();
    else if (action == nextAction_)
        currentPlayer_.next();
    else if (action == previousAction_)
        currentPlayer_.previous();
    else if (action == toggleFavoriteAction_)
        currentPlayer_.toggleFavoriteSong();
    else
        application_->restoreWindow();
}

int SingleInstance::runSecondaryApplication()
{
    LOG_DEBUG(logger_, "Running secondary application");
    
    localSocket_ = localSocketFactory_.create();
    connect(localSocket_.get(), &ILocalSocket::connected, this, &SingleInstance::onConnectedToPrimaryApplication);
    connect(localSocket_.get(), &ILocalSocket::error, this, &SingleInstance::onConnectionErrorWithPrimaryApplication);
    localSocket_->connectToServer(qApp->applicationName(), QIODevice::WriteOnly);

    auto retCode = qtApplication_.run();

    localSocket_->disconnectFromServer();

    return retCode;
}

void SingleInstance::onConnectedToPrimaryApplication()
{
    LOG_INFO(logger_, "connection with the primary application succeeded");
    QString action = requestedAcion();
    LOG_DEBUG(logger_, "sending action: " << action);
    localSocket_->write(action + "\n");
    QTimer::singleShot(1, [&](){ qtApplication_.exit(1); } );
}

void SingleInstance::onConnectionErrorWithPrimaryApplication()
{
    LOG_WARN(logger_, "could not connect to the primary application, quitting...");
    QTimer::singleShot(1, [&](){ qtApplication_.exit(2); } );
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

void SingleInstance::pollState()
{
    QFileInfo lockFile(lockFilePath_);
    if (!lockFile.exists()) {
        LOG_WARN(logger_, "lock file disappeared, trying to restore lock");
        if (lockFile_.tryLock(100))
            LOG_INFO(logger_, "lock restored");
    }

    QFileInfo serverFile(localServer_->serverSocketFilePath());
    if (!serverFile.exists()) {
        LOG_WARN(logger_, "server file diseappeared, trying to restore local server");
        localServer_->close();
        if (localServer_->listen())
        LOG_INFO(logger_, "local server restored");;
    }

}

bool SingleInstance::checkForPrimary()
{
    QLockFile lockFile(QDir::tempPath() + QDir::separator() + qApp->applicationName() + ".lock");
    lockFile.setStaleLockTime(0);
    bool primary = false;
    if (lockFile.tryLock(100)) {
        primary = true;
        lockFile.unlock();
    }
    return primary;
}
