#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <Mocks/PlayerMock.hpp>
#include <UnitTests/Domain/Settings/FakeSettingsStore.hpp>
#include <UnitTests/Presentation/FakeMainWindow.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("SystemTrayIconTests")
{

    auto playerMock = PlayerMock::get();
    FakeSettingsStore settingsStore;
    SettingsSchemaLoader loader;
    Settings settings(loader, settingsStore);
    FakeMainWindow mainWindow;
    SystemTrayIcon systemTrayIcon(playerMock.get(), mainWindow, settings);

    SECTION("show window onActivated")
    {
        systemTrayIcon.onActivated(QSystemTrayIcon::Context);
        REQUIRE(mainWindow.isShown);
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
        REQUIRE(mainWindow.isShown);
    }

    SECTION("quit quits the application")
    {
        systemTrayIcon.quit();
        REQUIRE(mainWindow.quitRequested);
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
