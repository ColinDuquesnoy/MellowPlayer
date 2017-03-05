#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Applications/Application.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("ApplicationTests") {
    auto mainWindowMock = MainWindowMock::get();
    auto hotkeysMock = HotkeysServiceMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto systemTrayIconMock = SystemTrayIconMock::get();
    Application app(qtAppMock.get(), mainWindowMock.get(), hotkeysMock.get(), systemTrayIconMock.get());

    SECTION("initialize") {
        app.initialize();
        Verify(Method(hotkeysMock, start)).Exactly(1);
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
