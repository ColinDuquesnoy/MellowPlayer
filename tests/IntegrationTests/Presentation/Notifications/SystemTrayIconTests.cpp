#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/SettingsStoreMock.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("SystemTrayIconTests")
{

    auto playerMock = PlayerMock::get();
    auto mainWindowMock = MainWindowMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto settingsStoreMock = SettingsStoreMock::get();
    SettingsSchemaLoader loader;
    Settings settings(loader, settingsStoreMock.get());
    SystemTrayIcon systemTrayIcon(playerMock.get(), mainWindowMock.get(), qtAppMock.get(), settings);

    SECTION("show window onActivated")
    {
        systemTrayIcon.onActivated(QSystemTrayIcon::Context);
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }

    SECTION("togglePlayPause call player")
    {
        systemTrayIcon.togglePlayPause();
        Verify(Method(playerMock, togglePlayPause)).Exactly(1);
    }

    SECTION("next call player")
    {
        systemTrayIcon.next();
        Verify(Method(playerMock, next)).Exactly(1);
    }

    SECTION("previous call player")
    {
        systemTrayIcon.previous();
        Verify(Method(playerMock, previous)).Exactly(1);
    }

    SECTION("restoreWindow show window")
    {
        systemTrayIcon.restoreWindow();
        Verify(Method(mainWindowMock, show)).Exactly(1);
    }

    SECTION("quit quits the application")
    {
        systemTrayIcon.quit();
        Verify(Method(qtAppMock, requestQuit)).Exactly(1);
    }

    SECTION("show icon")
    {
        systemTrayIcon.show();
    }
    SECTION("hide icon")
    {
        systemTrayIcon.hide();
    }
    SECTION("show message")
    {
        systemTrayIcon.showMessage("Title", "Message");
    }
}
