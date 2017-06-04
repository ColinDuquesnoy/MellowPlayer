#include <QVariant>
#include <catch.hpp>
#include <MellowPlayer/Application/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/FakeWorkDispatcher.hpp>
#include <Mocks/InMemoryListeningHistoryDataProvider.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <Utils/Helpers.hpp>
#include <DI.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)

TEST_CASE("ListeningHistoryTests") {
    auto mock = StreamingServiceLoaderMock::get();
    StreamingServices streamingServices(mock.get());
    streamingServices.load();
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    FakeWorkDispatcher workDispatcher;
    InMemoryListeningHistoryDataProvider dataProvider;
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    ListeningHistory listeningHistoryService(dataProvider, player, workDispatcher, settings);
    Player& currentPlayer = *players.get(streamingServices.getAll()[0]->getName());
    streamingServices.setCurrent(streamingServices.getAll()[0].get());
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
        Player& player2 = *players.get(streamingServices.getAll()[1]->getName());
        streamingServices.setCurrent(streamingServices.getAll()[1].get());
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