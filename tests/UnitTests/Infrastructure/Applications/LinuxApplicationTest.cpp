#include <QtCore>
#ifdef Q_OS_LINUX
#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/LinuxApplication.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/MprisServiceMock.hpp>
#include <Mocks/NotifierMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Infrastructure;

TEST_CASE("LinuxApplicationTests", "[UnitTest]")
{
    auto mainWindowMock = MainWindowMock::get();
    auto hotkeysMock = HotkeysControllerMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto mprisMock = MprisServiceMock::get();
    auto notificationServiceMock = NotifierMock::get();
    auto serviceLoaderMock = StreamingServiceLoaderMock::get();
    auto watcherMock = StreamingServiceWatcherMock::get();
    StreamingServicesController streamingServices(serviceLoaderMock.get(), watcherMock.get());
    auto systemTrayIconMock = SystemTrayIconMock::get();
    LinuxApplication app(qtAppMock.get(), mainWindowMock.get(), streamingServices, hotkeysMock.get(),
                         systemTrayIconMock.get(), notificationServiceMock.get(), mprisMock.get());

    SECTION("initialize")
    {
        app.initialize();
        Verify(Method(mainWindowMock, load)).Exactly(1);
        Verify(Method(systemTrayIconMock, show)).Exactly(1);
        Verify(Method(mprisMock, start)).Exactly(1);
    }
}
#endif
