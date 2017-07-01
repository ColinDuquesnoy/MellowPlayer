#include <catch.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistory/ListeningHistoryEntryModel.hpp>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("ListeningHistoryEntryModelTests") {
    Song song("uniqueId1", "title1", "artist1", "album1", "artUrl1", 5, false);
    Song song2("uniqueId2", "title2", "artist2", "album2", "artUrl2", 5, false);
    ListeningHistoryEntry entry = ListeningHistoryEntry::fromData(&song, "Deezer");
    ListeningHistoryEntryModel model(entry);

    REQUIRE(model.getSongId() == song.getUniqueId());
    REQUIRE(model.getTitle() == song.getTitle());
    REQUIRE(model.getArtist() == song.getArtist());
    REQUIRE(model.getArtUrl() == song.getArtUrl());
    REQUIRE(model.getService() == "Deezer");
    REQUIRE(!model.getDate().isEmpty());
    REQUIRE(!model.getTime().isEmpty());
    REQUIRE(model.getDateCategory() == "Today");
}