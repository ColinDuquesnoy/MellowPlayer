#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/SqlLiteListeningHistoryDatabase.hpp>
#include <QDir>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("SqlLiteListeningHistoryDataProviderTests", "[!mayfail]")
{
    QString dbPath = SqlLiteListeningHistoryDatabase::getDatabasePath();
    QDir().remove(dbPath);
    SqlLiteListeningHistoryDatabase dataProvider;
    bool initialized = dataProvider.initialize();
    dataProvider.clear();

    CAPTURE(dbPath.toStdString());
    REQUIRE(initialized);

    Song song1("uniqueId1", "title1", "artist1", "album1", "artUrl1", 5, false);
    Song song2("uniqueId2", "title2", "artist2", "album2", "artUrl2", 5, false);
    ListeningHistoryEntry defaultEntry;
    ListeningHistoryEntry entry1Deezer = ListeningHistoryEntry::fromData(&song1, "Deezer");
    ListeningHistoryEntry entry1DeezerBis = ListeningHistoryEntry::fromData(&song1, "Deezer");
    ListeningHistoryEntry entry2Deezer = ListeningHistoryEntry::fromData(&song2, "Deezer");
    ListeningHistoryEntry entry1Spotify = ListeningHistoryEntry::fromData(&song2, "Spotify");

    entry1Deezer.id = dataProvider.add(entry1Deezer);
    REQUIRE(entry1Deezer.id != -1);
    REQUIRE(dataProvider.toList().count() == 1);

    SECTION("Add entry")
    {
        int id = dataProvider.add(entry1Spotify);
        REQUIRE(id == 2);
        REQUIRE(dataProvider.toList().count() == 2);
    }

    SECTION("Remove by id")
    {
        dataProvider.remove("id", "1");
        REQUIRE(dataProvider.toList().count() == 0);
    }

    SECTION("Remove all deezer entries")
    {
        dataProvider.add(entry2Deezer);
        dataProvider.add(entry1Spotify);
        REQUIRE(dataProvider.toList().count() == 3);
        dataProvider.remove("serviceName", "Deezer");
        REQUIRE(dataProvider.toList().count() == 1);
    }

    SECTION("Remove many entries")
    {
        dataProvider.add(entry2Deezer);
        entry1Spotify.id = dataProvider.add(entry1Spotify);
        REQUIRE(dataProvider.toList().count() == 3);

        QList<int> toRemove;
        toRemove.append(entry1Deezer.id);
        toRemove.append(entry1Spotify.id);
        dataProvider.removeMany(toRemove);
        REQUIRE(dataProvider.toList().count() == 1);
    }
}
