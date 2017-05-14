#include <catch.hpp>
#include <MellowPlayer/Presentation/Widgets/QmlMainWindow.hpp>
#include <DI.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("QmlMainWindowTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);

    StreamingServicesViewModel& streamingServices = injector.create<StreamingServicesViewModel&>();
    ListeningHistoryViewModel& listeningHistory = injector.create<ListeningHistoryViewModel&>();
    StyleViewModel& style = injector.create<StyleViewModel&>();
    IPlayer& player = injector.create<PlayerProxy&>();
    ILocalAlbumArtService& albumArt = injector.create<ILocalAlbumArtService&>();
    IApplicationSettings& applicationSettings = injector.create<IApplicationSettings&>();

    QmlMainWindow mainWindow(streamingServices, listeningHistory, style, player, albumArt, applicationSettings);

    mainWindow.show();
    mainWindow.hide();
    REQUIRE(mainWindow.load());
    mainWindow.show();
    mainWindow.hide();
}
