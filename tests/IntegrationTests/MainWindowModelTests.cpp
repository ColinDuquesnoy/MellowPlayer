#include <catch.hpp>
#include <QtTest/QSignalSpy>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/Models/MainWindowModel.hpp>
#include <DI.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("QmlMainWindowTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);

    StreamingServicesModel& streamingServices = injector.create<StreamingServicesModel&>();
    ListeningHistoryModel& listeningHistory = injector.create<ListeningHistoryModel&>();
    StreamingServiceStyleModel& style = injector.create<StreamingServiceStyleModel&>();
    IPlayer& player = injector.create<CurrentPlayer&>();
    ILocalAlbumArt& albumArt = injector.create<ILocalAlbumArt&>();
    Settings& settings = injector.create<Settings&>();
    IQtApplication& qtApp = injector.create<IQtApplication&>();

    MainWindowModel mainWindow(streamingServices, listeningHistory, style, qtApp, player, albumArt, settings);
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
