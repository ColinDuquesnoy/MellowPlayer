#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <MellowPlayer/Entities/Notifications.hpp>
#include <MellowPlayer/Application/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/Infrastructure/Applications/LinuxApplication.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/MprisServiceMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>
#include <Mocks/NotificationServiceMock.hpp>
#include <Mocks/PluginLoaderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("LinuxApplicationTests", "[UnitTest]") {
    auto mainWindowMock = MainWindowMock::get();
    auto hotkeysMock = HotkeysServiceMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto mprisMock = MprisServiceMock::get();
    auto notificationServiceMock = NotificationServiceMock::get();
    auto pluginLoaderMock = PluginLoaderMock::get();
    StreamingServicePluginService pluginService(pluginLoaderMock.get());
    auto systemTrayIconMock = SystemTrayIconMock::get();
    LinuxApplication app(qtAppMock.get(),
                         mainWindowMock.get(),
                         pluginService,
                         hotkeysMock.get(),
                         systemTrayIconMock.get(),
                         notificationServiceMock.get(),
                         mprisMock.get());

    SECTION("initialize") {
        app.initialize();
        Verify(Method(mainWindowMock, load)).Exactly(1);
        Verify(Method(systemTrayIconMock, show)).Exactly(1);
        Verify(Method(mprisMock, start)).Exactly(1);
    }
}
#endif
