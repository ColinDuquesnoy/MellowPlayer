#include <catch.hpp>
#include <QtTest/QSignalSpy>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include "Utils/DependencyFactory.hpp";

using namespace MellowPlayer;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("MainWindowViewModel") {
    Tests::DependencyFactory dependencyFactory;
    MainWindowViewModel& mainWindow = dependencyFactory.createMainWindowViewModel();
    QSignalSpy visibleChangedSpy(&mainWindow, SIGNAL(visibleChanged()));

    REQUIRE(mainWindow.load());

    SECTION("show emit visibleChanged") {
        REQUIRE(!mainWindow.isVisible());
        REQUIRE(visibleChangedSpy.count() == 0);
        mainWindow.show();
        REQUIRE(mainWindow.isVisible());
        REQUIRE(visibleChangedSpy.count() == 1);

        SECTION("hide") {
            mainWindow.hide();
            REQUIRE(!mainWindow.isVisible());
            REQUIRE(visibleChangedSpy.count() == 2);
        }
    }
}
