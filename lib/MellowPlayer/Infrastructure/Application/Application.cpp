#include "Application.hpp"
#include "MellowPlayer/Presentation/IconProvider.hpp"
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <QtCore/QProcess>
#include <QtGui/QFontDatabase>
#include <QtWebEngineWidgets/QWebEngineProfile>

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
