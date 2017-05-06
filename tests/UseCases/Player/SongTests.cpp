#include <catch.hpp>
#include <MellowPlayer/Entities/Song.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

TEST_CASE("SongTests", "[UnitTest]") {

    SECTION("Parametrized ctor") {
        Song song("uniqueId", "title", "artist", "album", "artUrl", 1534, true);

        REQUIRE(song.getAlbum() == "album");
        REQUIRE(song.getArtist() == "artist");
        REQUIRE(song.getArtUrl() == "artUrl");
        REQUIRE(song.getDuration() == 1534);
        REQUIRE(song.getIsFavorite());
        REQUIRE(song.getTitle() == "title");
        REQUIRE(song.getUniqueId() == "uniqueId");
    }

    SECTION("NullCtor") {
        Song song;

        REQUIRE(song.getAlbum() == "");
        REQUIRE(song.getArtist() == "");
        REQUIRE(song.getArtUrl() == "");
        REQUIRE(song.getDuration() == 0);
        REQUIRE(!song.getIsFavorite());
        REQUIRE(song.getTitle() == "");
        REQUIRE(song.getUniqueId() == "");
    }

    SECTION("setDuration") {
        Song song;
        QSignalSpy spy(&song, SIGNAL(durationChanged()));

        song.setDuration(40);
        REQUIRE(song.getDuration() == 40);
        REQUIRE(spy.count() == 1);

        song.setDuration(40);
        REQUIRE(spy.count() == 1);
    }

    SECTION("setIsFavorite") {
        Song song;
        QSignalSpy spy(&song, SIGNAL(isFavoriteChanged()));

        song.setIsFavorite(true);
        REQUIRE(song.getIsFavorite());
        REQUIRE(spy.count() == 1);

        song.setIsFavorite(true);
        REQUIRE(spy.count() == 1);
    }

    SECTION("equality operator") {
        Song nullSong;
        Song song1("uniqueId1", "", "", "", "", 0, false);
        Song song1bis("uniqueId1", "", "", "", "", 0, false);
        Song song2("uniqueId2", "", "", "", "", 0, false);

        REQUIRE(nullSong == Song());
        REQUIRE(song1 == song1bis);
        REQUIRE(song1 != nullSong);
        REQUIRE(song1 != song2);
    }

    SECTION("isValid") {
        Song nullSong;
        REQUIRE(!nullSong.isValid());
        Song song1("uniqueId1", "title", "", "", "", 0, false);
        REQUIRE(song1.isValid());
    }
}