#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/LinuxApplication.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/MprisServiceMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>
#include <Mocks/NotifierMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("LinuxApplicationTests", "[UnitTest]") {
    auto mainWindowMock = MainWindowMock::get();
    auto hotkeysMock = HotkeysControllerMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto mprisMock = MprisServiceMock::get();
    auto notificationServiceMock = NotifierMock::get();
    auto pluginLoaderMock = StreamingServiceLoaderMock::get();
    StreamingServices streamingServices(pluginLoaderMock.get());
    auto systemTrayIconMock = SystemTrayIconMock::get();
    LinuxApplication app(qtAppMock.get(),
                         mainWindowMock.get(),
                         streamingServices,
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
