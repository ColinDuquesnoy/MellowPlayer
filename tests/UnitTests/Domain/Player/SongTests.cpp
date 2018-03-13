#include <MellowPlayer/Domain/Player/Song.hpp>
#include <QtTest/QSignalSpy>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

TEST_CASE("SongTests", "[UnitTest]")
{

    SECTION("Parametrized ctor")
    {
        Song song("uniqueId", "title", "artist", "album", "artUrl", 1534, true);

        REQUIRE(song.album() == "album");
        REQUIRE(song.artist() == "artist");
        REQUIRE(song.artUrl() == "artUrl");
        REQUIRE(song.duration() == 1534);
        REQUIRE(song.isFavorite());
        REQUIRE(song.title() == "title");
        REQUIRE(song.uniqueId() == "uniqueId");
    }

    SECTION("NullCtor")
    {
        Song song;

        REQUIRE(song.album() == "");
        REQUIRE(song.artist() == "");
        REQUIRE(song.artUrl() == "");
        REQUIRE(song.duration() == 0);
        REQUIRE(!song.isFavorite());
        REQUIRE(song.title() == "");
        REQUIRE(song.uniqueId() == "");
    }

    SECTION("setDuration")
    {
        Song song;
        QSignalSpy spy(&song, SIGNAL(durationChanged()));

        song.setDuration(40);
        REQUIRE(song.duration() == 40);
        REQUIRE(spy.count() == 1);

        song.setDuration(40);
        REQUIRE(spy.count() == 1);
    }

    SECTION("setFavorite")
    {
        Song song;
        QSignalSpy spy(&song, SIGNAL(isFavoriteChanged()));

        song.setFavorite(true);
        REQUIRE(song.isFavorite());
        REQUIRE(spy.count() == 1);

        song.setFavorite(true);
        REQUIRE(spy.count() == 1);
    }

    SECTION("equality operator")
    {
        Song nullSong;
        Song song1("uniqueId1", "", "", "", "", 0, false);
        Song song1bis("uniqueId1", "", "", "", "", 0, false);
        Song song2("uniqueId2", "", "", "", "", 0, false);

        REQUIRE(nullSong == Song());
        REQUIRE(song1 == song1bis);
        REQUIRE(song1 != nullSong);
        REQUIRE(song1 != song2);
    }

    SECTION("isValid")
    {
        Song nullSong;
        REQUIRE(!nullSong.isValid());
        Song song1("uniqueId1", "title", "", "", "", 0, false);
        REQUIRE(song1.isValid());
    }
}