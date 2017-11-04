#include <MellowPlayer/Domain/Notifications/Notifications.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Infrastructure/Applications/CoreApplication.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/NotifierMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Infrastructure;

TEST_CASE("CoreApplicationTests", "[UnitTest]")
{
    auto mainWindowMock = MainWindowMock::get();
    auto hotkeysMock = HotkeysControllerMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto systemTrayIconMock = SystemTrayIconMock::get();
    auto notificationServiceMock = NotifierMock::get();
    auto serviceLoaderMock = StreamingServiceLoaderMock::get();
    auto watcherMock = StreamingServiceWatcherMock::get();
    StreamingServicesController streamingServices(serviceLoaderMock.get(), watcherMock.get());
    CoreApplication app(qtAppMock.get(), mainWindowMock.get(), streamingServices, hotkeysMock.get(), systemTrayIconMock.get(),
                        notificationServiceMock.get());

    SECTION("initialize")
    {
        app.initialize();
        Verify(Method(mainWindowMock, load)).Exactly(1);
        Verify(Method(systemTrayIconMock, show)).Exactly(1);
    }

    SECTION("run")
    {
        app.run();
        Verify(Method(qtAppMock, run)).Exactly(1);
    }

    SECTION("restoreWindow")
    {
        app.restoreWindow();
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }

    SECTION("quit")
    {
        app.quit();
        Verify(Method(qtAppMock, quit)).Exactly(1);
    }
}
