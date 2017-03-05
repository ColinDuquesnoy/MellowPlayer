#pragma once

#include "Application.hpp"
#include "../Services/MprisService.hpp"

#ifdef Q_OS_LINUX

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class LinuxApplication: public Application {
public:
    LinuxApplication(UseCases::IQtApplication& qtApp, UseCases::IMainWindow& mainWindow, IHotkeysService& kotkeys,
                     UseCases::ISystemTrayIcon& systemTrayIcon, IMprisService& mprisService);
    void initialize() override;

private:
    IMprisService& mprisService;
};

END_MELLOWPLAYER_NAMESPACE

#endif
