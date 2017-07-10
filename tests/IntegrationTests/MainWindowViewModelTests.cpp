#include <catch.hpp>
#include <QtTest/QSignalSpy>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <DI.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("MainWindowViewModel") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);

    StreamingServicesControllerViewModel& streamingServices = injector.create<StreamingServicesControllerViewModel&>();
    ListeningHistoryViewModel& listeningHistory = injector.create<ListeningHistoryViewModel&>();
    StyleViewModel& style = injector.create<StyleViewModel&>();
    IPlayer& player = injector.create<CurrentPlayer&>();
    ILocalAlbumArt& albumArt = injector.create<ILocalAlbumArt&>();
    Settings& settings = injector.create<Settings&>();
    IQtApplication& qtApp = injector.create<IQtApplication&>();

    MainWindowViewModel mainWindow(streamingServices, listeningHistory, style, qtApp, player, settings);
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
