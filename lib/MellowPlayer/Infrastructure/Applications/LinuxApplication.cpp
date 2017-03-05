#include "LinuxApplication.hpp"

#ifdef Q_OS_LINUX

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

LinuxApplication::LinuxApplication(IQtApplication& qtApp,
                                   IMainWindow& mainWindow,
                                   IHotkeysService& kotkeys,
                                   ISystemTrayIcon& systemTrayIcon,
                                   IMprisService& mprisService) :
        Application(qtApp, mainWindow, kotkeys, systemTrayIcon), mprisService(mprisService) {

}

void LinuxApplication::initialize() {
    Application::initialize();
    mprisService.start();
}

#endif
