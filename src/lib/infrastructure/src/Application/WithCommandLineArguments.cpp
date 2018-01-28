#include <MellowPlayer/Infrastructure/Application/WithCommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <QtCore/QTimer>

using namespace MellowPlayer::Infrastructure;

WithCommandLineArguments::WithCommandLineArguments(const std::shared_ptr<IApplication>& application,
                                                   ICommandLineArguments& commandLineArguments)
        : ApplicationDecorator(application), commandLineArguments_(commandLineArguments)
{

}

void WithCommandLineArguments::initialize()
{
    commandLineArguments_.parse();

    if (commandLineArguments_.autoQuitDelay() != 0)
        QTimer::singleShot(commandLineArguments_.autoQuitDelay(), [&]() { application_->quit(); } );

    ApplicationDecorator::initialize();
}
