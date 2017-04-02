#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <MellowPlayer/UseCases/Plugin/PluginManager.hpp>
#include <MellowPlayer/UseCases/Notifications/Notifications.hpp>
#include <MellowPlayer/Infrastructure/Applications/LinuxApplication.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/MprisServiceMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>
#include <Mocks/NotificationServiceMock.hpp>
#include <Mocks/PluginLoaderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("LinuxApplicationTests") {
    auto mainWindowMock = MainWindowMock::get();
    auto hotkeysMock = HotkeysServiceMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto mprisMock = MprisServiceMock::get();
    auto notificationServiceMock = NotificationServiceMock::get();
    auto pluginLoaderMock = PluginLoaderMock::get();
    PluginManager pluginManager(pluginLoaderMock.get());
    auto systemTrayIconMock = SystemTrayIconMock::get();
    LinuxApplication app(qtAppMock.get(),
                         mainWindowMock.get(),
                         pluginManager,
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
