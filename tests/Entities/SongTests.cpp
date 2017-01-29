#include <catch.hpp>
#include <MellowPlayer/Entities.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

TEST_CASE("Song.DefaultCtor", "[Song]") {
    Song song;

    REQUIRE(song.album == "");
    REQUIRE(song.artist == "");
    REQUIRE(song.artUrl == "");
    REQUIRE(song.duration == 0);
    REQUIRE(!song.isFavorite);
    REQUIRE(song.title == "");
    REQUIRE(song.uniqueId == "");
}