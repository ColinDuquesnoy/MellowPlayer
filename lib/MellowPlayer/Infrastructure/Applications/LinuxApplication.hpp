#pragma once

#include "Application.hpp"
#include "../Services/MprisService.hpp"

#ifdef Q_OS_LINUX

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class LinuxApplication: public Application {
public:
    LinuxApplication(UseCases::IQtApplication& qtApp,
                     UseCases::IMainWindow& mainWindow,
                     UseCases::PluginManager& pluginManager,
                     UseCases::IHotkeysService& kotkeys,
                     UseCases::ISystemTrayIcon& systemTrayIcon,
                     UseCases::INotificationService& playerNotificationService,
                     UseCases::IMprisService& mprisService);
    void initialize() override;

private:
    UseCases::ILogger& logger;
    UseCases::IMprisService& mprisService;
};

END_MELLOWPLAYER_NAMESPACE

#endif
