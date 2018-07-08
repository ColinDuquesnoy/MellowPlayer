#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

TEST_CASE("ListeningHistoryEntryViewModelTests")
{
    Song song("uniqueId1", "title1", "artist1", "album1", "artUrl1", 5, false);
    Song song2("uniqueId2", "title2", "artist2", "album2", "artUrl2", 5, false);
    ListeningHistoryEntry entry = ListeningHistoryEntry::fromData(&song, "Deezer");
    ListeningHistoryEntryViewModel model(entry);

    REQUIRE(model.songId() == song.uniqueId());
    REQUIRE(model.title() == song.title());
    REQUIRE(model.artist() == song.artist());
    REQUIRE(model.artUrl() == song.artUrl());
    REQUIRE(model.service() == "Deezer");
    REQUIRE(!model.date().isEmpty());
    REQUIRE(!model.time().isEmpty());
    REQUIRE(model.dateCategory() == "Today");
}