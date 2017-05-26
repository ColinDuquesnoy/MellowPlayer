#include <QVariant>
#include <catch.hpp>
#include <MellowPlayer/UseCases/Services/ListeningHistoryService.hpp>
#include <MellowPlayer/UseCases/Player/PlayerProxy.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/FakeWorkDispatcher.hpp>
#include <Mocks/InMemoryListeningHistoryDataProvider.hpp>
#include <Mocks/PluginLoaderMock.hpp>
#include <MellowPlayer/UseCases/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/UseCases/Services/PlayerService.hpp>
#include <Utils/Helpers.hpp>
#include <DI.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

TEST_CASE("ListeningHistoryServiceTests") {
    auto mock = PluginLoaderMock::get();
    StreamingServicePluginService pluginService(mock.get());
    pluginService.load();
    PlayerService playerService(pluginService);
    PlayerProxy player(playerService, pluginService);
    FakeWorkDispatcher workDispatcher;
    InMemoryListeningHistoryDataProvider dataProvider;
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    ListeningHistoryService listeningHistoryService(dataProvider, player, workDispatcher, settings);
    Player& currentPlayer = *playerService.get(pluginService.getAll()[0]->getName());
    pluginService.setCurrent(pluginService.getAll()[0].get());
    Setting& isEnabledSetting = settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY);
    isEnabledSetting.setValue(true);

    SECTION("Initialize") {
        REQUIRE(!dataProvider.initialized);
        listeningHistoryService.initialize();
        REQUIRE(dataProvider.initialized);
    }

    SECTION("New song will be added to history") {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryService.count() == 1);
    }

    SECTION("Song will not be added to history when resumed after paused") {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryService.count() == 1);
        // pause
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", false));
        REQUIRE(listeningHistoryService.count() == 1);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", true));
        REQUIRE(listeningHistoryService.count() == 1);
    }

    SECTION("Clear history") {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        REQUIRE(listeningHistoryService.count() == 2);
        listeningHistoryService.clear();
        REQUIRE(listeningHistoryService.count() == 0);
    }

    SECTION("Remove by id") {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryService.count() == 3);
        listeningHistoryService.removeById(2);
        REQUIRE(listeningHistoryService.count() == 2);
        listeningHistoryService.removeById(2);
        REQUIRE(listeningHistoryService.count() == 2);
        listeningHistoryService.removeById(1);
        REQUIRE(listeningHistoryService.count() == 1);
        listeningHistoryService.removeById(3);
        REQUIRE(listeningHistoryService.count() == 0);
    }

    SECTION("Remove by service") {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        Player& player2 = *playerService.get(pluginService.getAll()[1]->getName());
        pluginService.setCurrent(pluginService.getAll()[1].get());
        player2.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryService.count() == 3);
        listeningHistoryService.removeByService(currentPlayer.getServiceName());
        REQUIRE(listeningHistoryService.count() == 1);
        listeningHistoryService.removeByService(currentPlayer.getServiceName());
        REQUIRE(listeningHistoryService.count() == 1);
        listeningHistoryService.removeByService(player2.getServiceName());
        REQUIRE(listeningHistoryService.count() == 0);
    }

    SECTION("Don't record song history if service is disabled") {
        isEnabledSetting.setValue(false);
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryService.count() == 0);
        isEnabledSetting.restoreDefaults();
    }

    SECTION("Clear history when service is disabled") {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryService.count() == 1);
        isEnabledSetting.setValue(false);
        REQUIRE(listeningHistoryService.count() == 0);
        isEnabledSetting.restoreDefaults();
    }

    isEnabledSetting.setValue(true);
}