#include <MellowPlayer/Presentation/Models/ListeningHistory/ListeningHistoryModel.hpp>
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
#include "DI.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("ListeningHistoryViewModelTests") {
    auto mock = StreamingServiceLoaderMock::get();
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    StreamingServices streamingServices(mock.get());
    streamingServices.load();
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    FakeWorkDispatcher workDispatcher;
    InMemoryListeningHistoryDataProvider dataProvider;
    Settings& settings = injector.create<Settings&>();
    ListeningHistory listeningHistoryService(dataProvider, player, workDispatcher, settings);
    Player& currentPlayer = *players.get(streamingServices.getAll()[0]->getName());
    streamingServices.setCurrent(streamingServices.getAll()[0].get());
    ListeningHistoryModel listeningHistoryViewModel(listeningHistoryService);
    Setting& isEnabledSetting = settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY);
    isEnabledSetting.setValue(true);
    
    SECTION("Initialize") {
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(!dataProvider.initialized);
        listeningHistoryViewModel.initialize();
        REQUIRE(dataProvider.initialized);
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 1);
    }

    listeningHistoryViewModel.initialize();

    SECTION("New song will be added to history") {
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 1);
    }

    SECTION("Song will not be added to history when resumed after paused") {
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 1);
        // pause
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", false));
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 1);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", true));
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 1);
    }

    SECTION("Remove by id") {
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 3);
        listeningHistoryViewModel.removeById(2);
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 2);
        listeningHistoryViewModel.removeById(2);
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 2);
        listeningHistoryViewModel.removeById(1);
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 1);
        listeningHistoryViewModel.removeById(3);
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 0);
    }

    SECTION("Remove by date category") {
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 3);
        listeningHistoryViewModel.removeByDateCategory("Today");
        REQUIRE(listeningHistoryViewModel.getSourceModel()->rowCount() == 0);
    }

    SECTION("Disable service") {
        REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 3);
        listeningHistoryViewModel.disableService(currentPlayer.getServiceName(), true);
        REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 0);
        listeningHistoryViewModel.disableService(currentPlayer.getServiceName(), false);
        REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 3);
    }

    SECTION("Search by title") {
        REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Rider on the storm", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Thriller", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Hey jude", "Id3"));
        REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 3);

        SECTION("common group of letters") {
            listeningHistoryViewModel.setSearchFilter("er");
            REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 2);
        }
        SECTION("whole word") {
            listeningHistoryViewModel.setSearchFilter("storm");
            REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 1);
        }
        SECTION("Entire title") {
            listeningHistoryViewModel.setSearchFilter("Hey jude");
            REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 1);

            SECTION("case does not matter") {
                listeningHistoryViewModel.setSearchFilter("HeY JuDe");
                REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 1);
            }
        }

        SECTION("Non existing title") {
            listeningHistoryViewModel.setSearchFilter("Yesterday");
            REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 0);
        }
    }

    SECTION("Search by artist") {
        REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id1", true, "The doors"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id2", true, "The beatles"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id3", true, "Georges Brassens"));
        REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 3);

        SECTION("common word") {
            listeningHistoryViewModel.setSearchFilter("The");
            REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 2);
        }
        SECTION("single letter") {
            listeningHistoryViewModel.setSearchFilter("s");
            REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 3);
        }
        SECTION("Entire name") {
            listeningHistoryViewModel.setSearchFilter("The beatLes");
            REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 1);
        }

        SECTION("Non existing title") {
            listeningHistoryViewModel.setSearchFilter("Daft Punk");
            REQUIRE(listeningHistoryViewModel.getFilteredModel()->rowCount() == 0);
        }
    }
}
