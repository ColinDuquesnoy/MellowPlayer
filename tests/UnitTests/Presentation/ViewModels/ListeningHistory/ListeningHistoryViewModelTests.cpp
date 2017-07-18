#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <QVariant>
#include <catch.hpp>
#include <MellowPlayer/Application/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/FakeWorkDispatcher.hpp>
#include <Mocks/InMemoryListeningHistoryDataProvider.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <Utils/DependencyPool.hpp>
#include <Utils/Helpers.hpp>


using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("ListeningHistoryViewModelTests") {
    DependencyPool pool;

    StreamingServicesController& streamingServices = pool.getStreamingServicesController();
    streamingServices.load();
    streamingServices.setCurrent(streamingServices.getAll()[0].get());

    Players& players = pool.getPlayers();
    Player& currentPlayer = *players.get(streamingServices.getAll()[0]->getName());

    Settings& settings = pool.getSettings();
    Setting& isEnabledSetting = settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY);
    isEnabledSetting.setValue(true);

    ListeningHistoryViewModel& listeningHistoryViewModel = pool.getListeningHistoryViewModel();
    
    SECTION("Initialize") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        listeningHistoryViewModel.initialize();
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
    }

    listeningHistoryViewModel.initialize();

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

    SECTION("Remove by id") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);
        listeningHistoryViewModel.removeById(2);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 2);
        listeningHistoryViewModel.removeById(2);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 2);
        listeningHistoryViewModel.removeById(1);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
        listeningHistoryViewModel.removeById(3);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
    }

    SECTION("Remove by date category") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);
        listeningHistoryViewModel.removeByDateCategory("Today");
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
    }

    SECTION("Disable service") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);
        listeningHistoryViewModel.disableService(currentPlayer.getServiceName(), true);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        listeningHistoryViewModel.disableService(currentPlayer.getServiceName(), false);
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);
    }

    SECTION("Search by title") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Rider on the storm", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Thriller", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Hey jude", "Id3"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);

        SECTION("common group of letters") {
            listeningHistoryViewModel.setSearchFilter("er");
            REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 2);
        }
        SECTION("whole word") {
            listeningHistoryViewModel.setSearchFilter("storm");
            REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
        }
        SECTION("Entire title") {
            listeningHistoryViewModel.setSearchFilter("Hey jude");
            REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);

            SECTION("case does not matter") {
                listeningHistoryViewModel.setSearchFilter("HeY JuDe");
                REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
            }
        }

        SECTION("Non existing title") {
            listeningHistoryViewModel.setSearchFilter("Yesterday");
            REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        }
    }

    SECTION("Search by artist") {
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id1", true, "The doors"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id2", true, "The beatles"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id3", true, "Georges Brassens"));
        REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);

        SECTION("common word") {
            listeningHistoryViewModel.setSearchFilter("The");
            REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 2);
        }
        SECTION("single letter") {
            listeningHistoryViewModel.setSearchFilter("s");
            REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 3);
        }
        SECTION("Entire name") {
            listeningHistoryViewModel.setSearchFilter("The beatLes");
            REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 1);
        }

        SECTION("Non existing title") {
            listeningHistoryViewModel.setSearchFilter("Daft Punk");
            REQUIRE(listeningHistoryViewModel.getModel()->rowCount() == 0);
        }
    }
}
