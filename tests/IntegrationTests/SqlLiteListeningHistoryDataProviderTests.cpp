#include <catch.hpp>
#include <QDir>
#include <MellowPlayer/Application/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/SqlLiteListeningHistoryDataProvider.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("SqlLiteListeningHistoryDataProviderTests") {
    QString dbPath = SqlLiteListeningHistoryDataProvider::getDatabasePath();
    QDir().remove(dbPath);
    SqlLiteListeningHistoryDataProvider dataProvider;
    dataProvider.initialize();
    dataProvider.clear();

    Song song1("uniqueId1", "title1", "artist1", "album1", "artUrl1", 5, false);
    Song song2("uniqueId2", "title2", "artist2", "album2", "artUrl2", 5, false);
    ListeningHistoryEntry defaultEntry;
    ListeningHistoryEntry entry1Deezer = ListeningHistoryEntry::fromData(&song1, "Deezer");
    ListeningHistoryEntry entry1DeezerBis = ListeningHistoryEntry::fromData(&song1, "Deezer");
    ListeningHistoryEntry entry2Deezer = ListeningHistoryEntry::fromData(&song2, "Deezer");
    ListeningHistoryEntry entry1Spotify = ListeningHistoryEntry::fromData(&song2, "Spotify");

    dataProvider.add(entry1Deezer);

    SECTION("Add entry") {
        REQUIRE(dataProvider.getAll().count() == 1);
        int id = dataProvider.add(entry1Spotify);
        REQUIRE(id == 2);
        REQUIRE(dataProvider.getAll().count() == 2);
    }

    SECTION("Remove by id") {
        REQUIRE(dataProvider.getAll().count() == 1);
        dataProvider.remove("id", "1");
        REQUIRE(dataProvider.getAll().count() == 0);
    }

    SECTION("Remove all deezer entries") {
        dataProvider.add(entry2Deezer);
        dataProvider.add(entry1Spotify);
        REQUIRE(dataProvider.getAll().count() == 3);
        dataProvider.remove("serviceName", "Deezer");
        REQUIRE(dataProvider.getAll().count() == 1);
    }
}

