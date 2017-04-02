#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Presentation/QtWebApplication.hpp>
#include <MellowPlayer/Infrastructure/Applications/SingleInstanceApplication.hpp>
#include "DI.hpp"

namespace di = boost::di;
using namespace std;
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)


int main(int argc, char** argv)
{
#ifdef Q_OS_WIN32
    Q_INIT_RESOURCE(presentation);
#endif
    SpdLoggerFactory loggerFactory;
    LoggingManager::initialize(loggerFactory, LogLevel::Debug);
    QtWebApplication qtApp(argc, argv);
    ScopedScope scope{};
    auto injector = di::make_injector(
        di::bind<IQtApplication>().to(qtApp),
        defaultInjector(scope),
        platformInjector(scope),
        notificationPresenterInjector(scope)
    );

    SingleInstanceApplication& app = injector.create<SingleInstanceApplication&>();
    return app.run();
}
