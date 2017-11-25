#include "ApplicationDecorator.hpp"

using namespace MellowPlayer::Infrastructure;

ApplicationDecorator::ApplicationDecorator(IApplication& application)
        : application_(application)
{
    connect(&application, &IApplication::started, this, &IApplication::started);
    connect(&application, &IApplication::initialized, this, &IApplication::initialized);
    connect(&application, &IApplication::restoreWindowRequest, this, &IApplication::restoreWindowRequest);
    connect(&application, &IApplication::commitDataRequest, this, &IApplication::commitDataRequest);
}

void ApplicationDecorator::initialize()
{
    application_.initialize();
}

int ApplicationDecorator::run()
{
    return application_.run();
}

void ApplicationDecorator::quit()
{
    application_.quit();
}

void ApplicationDecorator::restart()
{
    application_.restart();
}

void ApplicationDecorator::restoreWindow()
{
    application_.restoreWindow();
}
