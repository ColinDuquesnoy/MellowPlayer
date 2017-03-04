#pragma once

#include <MellowPlayer/UseCases.hpp>
#include "IApplication.hpp"
#include "../Services/HotkeysService.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Application : public IApplication {
public:
    Application(UseCases::IQtApplication& qtApp, UseCases::IMainWindow& mainWindow, IHotkeysService& kotkeys);

    void initialize() override;
    void restoreWindow() override;
    int run() override;
    void quit() override;

private:
    UseCases::IQtApplication& qtApp;
    UseCases::IMainWindow& mainWindow;
    IHotkeysService& kotkeys;
};

END_MELLOWPLAYER_NAMESPACE
