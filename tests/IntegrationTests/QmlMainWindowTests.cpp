#include <catch.hpp>
#include <MellowPlayer/UseCases/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/Widgets/QmlMainWindow.hpp>
#include <DI.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("QmlMainWindowTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);

    StreamingServicesModel& streamingServices = injector.create<StreamingServicesModel&>();
    ListeningHistoryModel& listeningHistory = injector.create<ListeningHistoryModel&>();
    StreamingServiceStyleModel& style = injector.create<StreamingServiceStyleModel&>();
    IPlayer& player = injector.create<PlayerProxy&>();
    ILocalAlbumArtService& albumArt = injector.create<ILocalAlbumArtService&>();
    Settings& settings = injector.create<Settings&>();

    QmlMainWindow mainWindow(streamingServices, listeningHistory, style, player, albumArt, settings);

    mainWindow.show();
    mainWindow.hide();
    REQUIRE(mainWindow.load());
    mainWindow.show();
    mainWindow.hide();
}
