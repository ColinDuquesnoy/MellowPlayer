#include "Program.hpp"
#include "DI.hpp"
#include <QtCore>
#ifdef Q_OS_WIN32
    #include <Windows.h>
#endif
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <QtQuickControls2/QQuickStyle>
#include <QtWebEngine>

namespace di = boost::di;
using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Main;

Program::Program(IApplication& application,
                 IContextProperties& contextProperties,
                 IMprisService& mprisService,
                 IViewModels& viewModels,
                 ISystemTrayIcon& systemTrayIcon,
                 INotifications& notifications,
                 IHotkeys& hotkeys)
        : application_(application),
          contextProperties_(contextProperties),
          mprisService_(mprisService),
          viewModels_(viewModels),
          systemTrayIcon_(systemTrayIcon),
          notifications_(notifications),
          hotkeys_(hotkeys)
{
    connect(&application, &IApplication::initialized, this, &Program::initialize);
    connect(&application, &IApplication::finished, this, &Program::finished);
}

int Program::run()
{
    application_.initialize();
    return application_.run();
}

void Program::initialize()
{
    mprisService_.start();
    hotkeys_.initialize();
    contextProperties_.initialize();
    viewModels_.initialize();
    notifications_.initialize();
    systemTrayIcon_.show();
}

void Program::finished()
{
    viewModels_.cleanup();
}

int Program::main(int argc, char** argv)
{
    qputenv("QTWEBENGINE_DIALOG_SET", "QtQuickControls2");
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "4242");

    QApplication qApplication(argc, argv);

    QQuickStyle::setStyle("Material");
    QtWebEngine::initialize();

    SpdLoggerFactory loggerFactory;
    Loggers::initialize(loggerFactory);

    ScopedScope scope{};
    auto injector = di::make_injector(di::bind<QApplication>().to(qApplication),
                                      defaultInjector(scope),
                                      platformInjector(scope),
                                      notificationPresenterInjector(scope));
    auto& program = injector.create<Program&>();
    return program.run();
}
