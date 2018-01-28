#include <MellowPlayer/Infrastructure/Application/ApplicationDecorator.hpp>

using namespace std;
using namespace MellowPlayer::Infrastructure;

ApplicationDecorator::ApplicationDecorator(const shared_ptr<IApplication>& application): application_(application)
{
    connect(application_.get(), &IApplication::started, this, &IApplication::started);
    connect(application_.get(), &IApplication::initialized, this, &IApplication::initialized);
    connect(application_.get(), &IApplication::finished, this, &IApplication::finished);
    connect(application_.get(), &IApplication::restoreWindowRequest, this, &IApplication::restoreWindowRequest);
    connect(application_.get(), &IApplication::commitDataRequest, this, &IApplication::commitDataRequest);
}

void ApplicationDecorator::initialize()
{
    application_->initialize();
}

int ApplicationDecorator::run()
{
    return application_->run();
}

void ApplicationDecorator::quit()
{
    application_->quit();
}

void ApplicationDecorator::restart()
{
    application_->restart();
}

void ApplicationDecorator::restoreWindow()
{
    application_->restoreWindow();
}
