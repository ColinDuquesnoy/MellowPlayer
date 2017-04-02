#include <catch.hpp>
#include <MellowPlayer/Entities/Notifications.hpp>
#include <MellowPlayer/UseCases/Services/PluginsService.hpp>
#include <MellowPlayer/Infrastructure/Applications/Application.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/NotificationServiceMock.hpp>
#include <Mocks/PluginLoaderMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("ApplicationTests") {
    auto mainWindowMock = MainWindowMock::get();
    auto hotkeysMock = HotkeysServiceMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto systemTrayIconMock = SystemTrayIconMock::get();
    auto notificationServiceMock = NotificationServiceMock::get();
    auto pluginLoaderMock = PluginLoaderMock::get();
    PluginsService pluginManager(pluginLoaderMock.get());
    Application app(qtAppMock.get(),
                    mainWindowMock.get(),
                    pluginManager,
                    hotkeysMock.get(),
                    systemTrayIconMock.get(),
                    notificationServiceMock.get());

    SECTION("initialize") {
        app.initialize();
        Verify(Method(mainWindowMock, load)).Exactly(1);
        Verify(Method(systemTrayIconMock, show)).Exactly(1);
    }

    SECTION("run") {
        app.run();
        Verify(Method(qtAppMock, run)).Exactly(1);
    }

    SECTION("restoreWindow") {
        app.restoreWindow();
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }

    SECTION("quit") {
        app.quit();
        Verify(Method(qtAppMock, quit)).Exactly(1);
    }
}
