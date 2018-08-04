#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/Application/WithLogging.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

WithLogging::WithLogging(const std::shared_ptr<IApplication>& application,
                         ICommandLineArguments& commandLineArguments)
        : ApplicationDecorator(application), commandLineArguments_(commandLineArguments)
{

}

void WithLogging::initialize()
{
    Loggers::instance().setDefaultLogLevel(commandLineArguments_.logLevel());

    auto& logger = Loggers::logger("main");
    auto logDirectory = FileHelper::logDirectory();
    auto version = BuildConfig::getVersion();
    auto buildInfo = BuildConfig::buildInfo();
    LOG_INFO(logger, "****************************** Starting ***************************************");
    LOG_INFO(logger, QString("MellowPlayer %1 - %2").arg(version).arg(buildInfo));
    LOG_INFO(logger, "Log directory: " + logDirectory);

    ApplicationDecorator::initialize();
}
