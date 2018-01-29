#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;

TEST_CASE("ListeningHistoryEntryTests")
{
    Song song1("uniqueId1", "title1", "artist1", "album1", "artUrl1", 5, false);
    Song song2("uniqueId2", "title2", "artist2", "album2", "artUrl2", 5, false);

    ListeningHistoryEntry defaultEntry;
    ListeningHistoryEntry entry1Deezer = ListeningHistoryEntry::fromData(&song1, "Deezer");
    entry1Deezer.id = 1;
    ListeningHistoryEntry entry1DeezerBis = ListeningHistoryEntry::fromData(&song1, "Deezer");
    entry1DeezerBis.id = 1;
    ListeningHistoryEntry entry2Deezer = ListeningHistoryEntry::fromData(&song2, "Deezer");
    entry2Deezer.id = 2;
    ListeningHistoryEntry entry1Spotify = ListeningHistoryEntry::fromData(&song2, "Spotify");
    entry1Spotify.id = 3;

    SECTION("default fields")
    {
        REQUIRE(defaultEntry.serviceName.isEmpty());
        REQUIRE(defaultEntry.time.isEmpty());
    }

    SECTION("fromData has basic song properties")
    {
        REQUIRE(entry1Deezer.serviceName == "Deezer");
        REQUIRE(entry1Deezer.songUniqueId == song1.uniqueId());
        REQUIRE(entry1Deezer.songTitle == song1.title());
        REQUIRE(entry1Deezer.artist == song1.artist());
        REQUIRE(entry1Deezer.album == song1.album());
        REQUIRE(entry1Deezer.artUrl == song1.artUrl());
        REQUIRE(!entry1Deezer.time.isEmpty());
    }

    SECTION("dateTime is valid")
    {
        REQUIRE(entry1Deezer.dateTime().isValid());
    }

    SECTION("isValid")
    {
        REQUIRE(!defaultEntry.isValid());
        REQUIRE(entry1Deezer.isValid());
    }

    SECTION("equals")
    {
        REQUIRE(entry1Deezer.equals(entry1DeezerBis));
        REQUIRE(!entry1Deezer.equals(entry2Deezer));
        REQUIRE(!entry1Deezer.equals(entry1Spotify));
    }

    SECTION("equality comparator uses id only")
    {
        REQUIRE(entry1Deezer == entry1DeezerBis);
        REQUIRE(entry1Deezer != entry2Deezer);
    }

    SECTION("implicit cast to int return id")
    {
        REQUIRE((int)entry1Deezer == entry1Deezer.id);
    }
}
