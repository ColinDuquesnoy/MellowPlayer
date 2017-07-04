#include <QtCore>
#ifdef Q_OS_WIN32
    #include <Windows.h>
#endif
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Infrastructure/Utils/FileHelper.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Infrastructure/Applications/SingleInstanceApplication.hpp>
#include "DI.hpp"

namespace di = boost::di;
using namespace std;
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)


int main(int argc, char** argv)
{
    // Init resources embedded in static libraries
    Q_INIT_RESOURCE(application);
    Q_INIT_RESOURCE(presentation);

    ApplicationViewModel qtApp(argc, argv);

    SpdLoggerFactory loggerFactory;
    LoggingManager::initialize(loggerFactory, LogLevel::Debug);
    ScopedScope scope{};

    LOG_INFO(LoggingManager::instance().getLogger("main"), "Log directory: " + FileHelper::logDirectory());

    auto injector = di::make_injector(
        di::bind<IQtApplication>().to(qtApp),
        defaultInjector(scope),
        platformInjector(scope),
        notificationPresenterInjector(scope)
    );

#ifdef QT_DEBUG
    IApplication& app = injector.create<IApplication&>();
    app.initialize();
#else
    SingleInstanceApplication& app = injector.create<SingleInstanceApplication&>();
#endif
    auto retCode = app.run();

    if (qtApp.restartRequested())
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

    return retCode;
}
