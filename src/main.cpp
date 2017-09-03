#include <QtCore>
#ifdef Q_OS_WIN32
#include <Windows.h>
#endif
#include "DI.hpp"
#include <MellowPlayer/Infrastructure/Applications/SingleInstanceApplication.hpp>
#include <MellowPlayer/Infrastructure/CommandLineParser.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Application/BuildConfig.hpp>

namespace di = boost::di;
using namespace std;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

int main(int argc, char** argv)
{
    // Init resources embedded in static libraries
    Q_INIT_RESOURCE(application);
    Q_INIT_RESOURCE(presentation);
    qputenv("QTWEBENGINE_DIALOG_SET", "QtQuickControls2");

    // commented on purpose, see github issue #71
    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    ApplicationViewModel qtApp(argc, argv);

    CommandLineParser commandLineParser;
    qtApp.setAutoQuitDelay(commandLineParser.autoQuitDelay());

    SpdLoggerFactory loggerFactory;
    LoggingManager::initialize(loggerFactory, commandLineParser.logLevel());
    ScopedScope scope{};
    LOG_INFO(LoggingManager::logger("main"), "Log directory: " + FileHelper::logDirectory());
    LOG_INFO(LoggingManager::logger("main"), QString("MellowPlayer %1 - %2").arg(QString(BuildConfig::getVersion())).arg(qtApp.buildInfo()));

    qtApp.initialize();

    auto injector = di::make_injector(di::bind<IQtApplication>().to(qtApp), di::bind<ICommandLineParser>().to(commandLineParser),
                                      defaultInjector(scope), platformInjector(scope), notificationPresenterInjector(scope));

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
