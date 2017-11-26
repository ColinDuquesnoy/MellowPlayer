#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Domain/BuildConfig.hpp>
#include "WithLogging.hpp"

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

WithLogging::WithLogging(IApplication& application,
                         unique_ptr<ILoggerFactory>& loggerFactory,
                         ICommandLineArguments& commandLineArguments)
        : ApplicationDecorator(application), loggerFactory_(loggerFactory), commandLineArguments_(commandLineArguments)
{

}

void WithLogging::initialize()
{
    LoggingManager::initialize(loggerFactory_, commandLineArguments_.logLevel());

    auto& logger = LoggingManager::logger("main");
    auto logDirectory = FileHelper::logDirectory();
    auto version = BuildConfig::getVersion();
    auto buildInfo = BuildConfig::buildInfo();

    LOG_INFO(logger, QString("MellowPlayer %1 - %2").arg(version).arg(buildInfo));
    LOG_INFO(logger, "Log directory: " + logDirectory);

    ApplicationDecorator::initialize();
}
