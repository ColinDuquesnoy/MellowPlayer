#include "LinuxApplication.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

LinuxApplication::LinuxApplication(IQtApplication& qtApp,
                                   IMainWindow& mainWindow,
                                   HotkeysService& kotkeys,
                                   MprisService& mprisService) : Application(qtApp, mainWindow, kotkeys),
                                                                 mprisService(mprisService) {

}

void LinuxApplication::initialize() {
    Application::initialize();
    mprisService.startService();
}
