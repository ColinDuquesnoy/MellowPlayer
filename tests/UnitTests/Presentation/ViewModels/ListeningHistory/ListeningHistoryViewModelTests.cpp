#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <Mocks/FakeListeningHistoryDatabase.hpp>
#include <Mocks/PlayerMock.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceLoader.hpp>
#include <Utils/DependencyPool.hpp>
#include <Utils/Helpers.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("ListeningHistoryViewModelTests")
{
    DependencyPool pool;

    StreamingServices& streamingServices = pool.getStreamingServices();
    streamingServices.load();
    streamingServices.setCurrent(streamingServices.toList()[0].get());

    Players& players = pool.getPlayers();
    Player& currentPlayer = *players.get(streamingServices.toList()[0]->name());

    Settings& settings = pool.getSettings();
    Setting& isEnabledSetting = settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY);
    isEnabledSetting.setValue(true);

    ListeningHistoryViewModel& listeningHistoryViewModel = pool.getListeningHistoryViewModel();

    SECTION("Initialize")
    {
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        listeningHistoryViewModel.initialize();
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
    }

    listeningHistoryViewModel.initialize();

    SECTION("New song will be added to history")
    {
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
    }

    SECTION("Song will not be added to history when resumed after paused")
    {
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
        // pause
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", false));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", true));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
    }

    SECTION("Remove by id")
    {
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 3);
        listeningHistoryViewModel.removeById(2);
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 2);
        listeningHistoryViewModel.removeById(2);
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 2);
        listeningHistoryViewModel.removeById(1);
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
        listeningHistoryViewModel.removeById(3);
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
    }

    SECTION("Remove by date category")
    {
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 3);
        listeningHistoryViewModel.removeByDateCategory("Today");
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
    }

    SECTION("Disable service")
    {
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 3);
        listeningHistoryViewModel.disableService(currentPlayer.serviceName(), true);
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        listeningHistoryViewModel.disableService(currentPlayer.serviceName(), false);
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 3);
    }

    SECTION("Search by title")
    {
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Rider on the storm", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Thriller", "Id2"));
        currentPlayer.setUpdateResults(getSongVariantMap("Hey jude", "Id3"));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 3);

        SECTION("common group of letters")
        {
            listeningHistoryViewModel.setSearchFilter("er");
            REQUIRE(listeningHistoryViewModel.model()->rowCount() == 2);
        }
        SECTION("whole word")
        {
            listeningHistoryViewModel.setSearchFilter("storm");
            REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
        }
        SECTION("Entire title")
        {
            listeningHistoryViewModel.setSearchFilter("Hey jude");
            REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);

            SECTION("case does not matter")
            {
                listeningHistoryViewModel.setSearchFilter("HeY JuDe");
                REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
            }
        }

        SECTION("Non existing title")
        {
            listeningHistoryViewModel.setSearchFilter("Yesterday");
            REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        }
    }

    SECTION("Search by artist")
    {
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id1", true, "The doors"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id2", true, "The beatles"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song", "Id3", true, "Georges Brassens"));
        REQUIRE(listeningHistoryViewModel.model()->rowCount() == 3);

        SECTION("common word")
        {
            listeningHistoryViewModel.setSearchFilter("The");
            REQUIRE(listeningHistoryViewModel.model()->rowCount() == 2);
        }
        SECTION("single letter")
        {
            listeningHistoryViewModel.setSearchFilter("s");
            REQUIRE(listeningHistoryViewModel.model()->rowCount() == 3);
        }
        SECTION("Entire name")
        {
            listeningHistoryViewModel.setSearchFilter("The beatLes");
            REQUIRE(listeningHistoryViewModel.model()->rowCount() == 1);
        }

        SECTION("Non existing title")
        {
            listeningHistoryViewModel.setSearchFilter("Daft Punk");
            REQUIRE(listeningHistoryViewModel.model()->rowCount() == 0);
        }
    }
}
