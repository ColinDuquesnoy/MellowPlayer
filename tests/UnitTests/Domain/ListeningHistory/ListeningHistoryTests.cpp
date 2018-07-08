#include <catch/catch.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <Utils/DependencyPool.hpp>
#include <Utils/Helpers.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

TEST_CASE("ListeningHistoryTests")
{
    MellowPlayer::Tests::DependencyPool pool;
    StreamingServices& streamingServices = pool.getStreamingServices();
    streamingServices.load();
    Players& players = pool.getPlayers();
    Settings& settings = pool.getSettings();
    ListeningHistory& listeningHistoryService = pool.getListeningHistory();
    Player& currentPlayer = *players.get(streamingServices.toList()[0]->name());
    streamingServices.setCurrent(streamingServices.toList()[0].get());
    Setting& isEnabledSetting = settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY);
    isEnabledSetting.setValue(true);

    SECTION("New song will be added to history")
    {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryService.count() == 1);
    }

    SECTION("Song will not be added to history when resumed after paused")
    {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryService.count() == 1);
        // pause
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", false));
        REQUIRE(listeningHistoryService.count() == 1);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1", true));
        REQUIRE(listeningHistoryService.count() == 1);
    }

    SECTION("Clear history")
    {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        REQUIRE(listeningHistoryService.count() == 2);
        listeningHistoryService.clear();
        REQUIRE(listeningHistoryService.count() == 0);
    }

    SECTION("Remove by id")
    {
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

    SECTION("Remove by service")
    {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        currentPlayer.setUpdateResults(getSongVariantMap("Song2", "Id2"));
        Player& player2 = *players.get(streamingServices.toList()[1]->name());
        streamingServices.setCurrent(streamingServices.toList()[1].get());
        player2.setUpdateResults(getSongVariantMap("Song3", "Id3"));
        REQUIRE(listeningHistoryService.count() == 3);
        listeningHistoryService.removeByService(currentPlayer.serviceName());
        REQUIRE(listeningHistoryService.count() == 1);
        listeningHistoryService.removeByService(currentPlayer.serviceName());
        REQUIRE(listeningHistoryService.count() == 1);
        listeningHistoryService.removeByService(player2.serviceName());
        REQUIRE(listeningHistoryService.count() == 0);
    }

    SECTION("Don't record song history if service is disabled")
    {
        isEnabledSetting.setValue(false);
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryService.count() == 0);
        isEnabledSetting.restoreDefaults();
    }

    SECTION("Clear history when service is disabled")
    {
        REQUIRE(listeningHistoryService.count() == 0);
        currentPlayer.setUpdateResults(getSongVariantMap("Song1", "Id1"));
        REQUIRE(listeningHistoryService.count() == 1);
        isEnabledSetting.setValue(false);
        REQUIRE(listeningHistoryService.count() == 0);
        isEnabledSetting.restoreDefaults();
    }

    isEnabledSetting.setValue(true);
}
