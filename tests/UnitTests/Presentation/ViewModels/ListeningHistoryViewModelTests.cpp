#include <MellowPlayer/Presentation/ViewModels/ListeningHistoryViewModel.hpp>
#include <QVariant>
#include <catch.hpp>
#include <MellowPlayer/UseCases/Services/ListeningHistoryService.hpp>
#include <MellowPlayer/UseCases/Player/PlayerProxy.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/FakeWorkDispatcher.hpp>
#include <Mocks/InMemoryListeningHistoryDataProvider.hpp>
#include <Mocks/PluginLoaderMock.hpp>
#include <MellowPlayer/UseCases/Services/PluginService.hpp>
#include <MellowPlayer/UseCases/Services/PlayerService.hpp>
#include <Utils/Helpers.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("ListeningHistoryViewModelTests") {
    auto mock = PluginLoaderMock::get();
    PluginService pluginService(mock.get());
    pluginService.load();
    PlayerService playerService(pluginService);
    PlayerProxy player(playerService, pluginService);
    FakeWorkDispatcher workDispatcher;
    InMemoryListeningHistoryDataProvider dataProvider;
    ListeningHistoryService listeningHistoryService(dataProvider, player, workDispatcher);
    Player& currentPlayer = *playerService.get(pluginService.getAll()[0]->getName());
    pluginService.setCurrent(pluginService.getAll()[0].get());
    ListeningHistoryViewModel listeningHistoryViewModel(listeningHistoryService);
    
    SECTION("Initialize") {
        REQUIRE(!dataProvider.initialized);
        listeningHistoryViewModel.initialize();
        REQUIRE(dataProvider.initialized);
    }


    SECTION("New song will be added to history") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
    }

    SECTION("Song will not be added to history when resumed after paused") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
        // pause
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", false));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", true));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
    }

    SECTION("Clear history") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 2);
        listeningHistoryService.clear();
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
    }

    SECTION("Remove by id") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);
        listeningHistoryService.removeById(2);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 2);
        listeningHistoryService.removeById(2);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 2);
        listeningHistoryService.removeById(1);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
        listeningHistoryService.removeById(3);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
    }

    SECTION("Remove by service") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        Player& player2 = *playerService.get(pluginService.getAll()[1]->getName());
        pluginService.setCurrent(pluginService.getAll()[1].get());
        player2.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);
        listeningHistoryService.removeByService(currentPlayer.getServiceName());
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
        listeningHistoryService.removeByService(currentPlayer.getServiceName());
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
        listeningHistoryService.removeByService(player2.getServiceName());
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
    }
}