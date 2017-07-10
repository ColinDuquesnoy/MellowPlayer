#include <catch.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("ListeningHistoryEntryViewModelTests") {
    Song song("uniqueId1", "title1", "artist1", "album1", "artUrl1", 5, false);
    Song song2("uniqueId2", "title2", "artist2", "album2", "artUrl2", 5, false);
    ListeningHistoryEntry entry = ListeningHistoryEntry::fromData(&song, "Deezer");
    ListeningHistoryEntryViewModel model(entry);

    REQUIRE(model.getSongId() == song.getUniqueId());
    REQUIRE(model.getTitle() == song.getTitle());
    REQUIRE(model.getArtist() == song.getArtist());
    REQUIRE(model.getArtUrl() == song.getArtUrl());
    REQUIRE(model.getService() == "Deezer");
    REQUIRE(!model.getDate().isEmpty());
    REQUIRE(!model.getTime().isEmpty());
    REQUIRE(model.getDateCategory() == "Today");
}