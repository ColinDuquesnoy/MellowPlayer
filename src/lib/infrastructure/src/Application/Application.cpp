#include <MellowPlayer/Infrastructure/Application/Application.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <QtCore/QProcess>
#include <QtCore/QDebug>

using namespace std;
using namespace MellowPlayer::Infrastructure;

Application::Application(IQtApplication& qtApplication)
        : qtApp_(qtApplication), restartRequested_(false)
{
    connect(&qtApp_, &IQtApplication::commitDataRequest, this, &Application::commitDataRequest);
}

void Application::initialize()
{
    emit initialized();
}

int Application::run()
{
    emit started();
    auto returnCode = qtApp_.run();
    emit finished();

    if (restartRequested_) {
        qWarning() << "restarting application...";
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }

    return returnCode;
}

void Application::quit()
{
    qtApp_.exit(0);
}

void Application::restart()
{
    restartRequested_ = true;
    quit();
}

void Application::restoreWindow()
{
    emit restoreWindowRequest();
}
