#include <QSignalSpy>
#include <catch.hpp>
#include <Entities/Song.hpp>


USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

void testQStringProperty(string propertyName, string signalName,
                         QString originalValue = "", QString value1 = "value1", QString value2 = "value2") {

    Song song;
    SECTION(propertyName + " has a default value equals to " + originalValue.toStdString()) {
        REQUIRE(song.property(propertyName.c_str()).toString().toStdString() == originalValue.toStdString());
    }

    SECTION(propertyName + " will change to  " + value1.toStdString()) {

        song.setProperty(propertyName.c_str(), value1);
        REQUIRE(song.property(propertyName.c_str()).toString().toStdString() == value1.toStdString());

        QSignalSpy spy(&song, signalName.c_str());

        SECTION(signalName + " is emitted when a different value is set") {
            song.setProperty(propertyName.c_str(), value2);
            REQUIRE(spy.count() == 1);
        }

        SECTION(signalName + " is not emitted when the same value is set") {
            song.setProperty(propertyName.c_str(), value1);
            REQUIRE(spy.count() == 0);
        }
    }
}

TEST_CASE("test song properties", "[Song]") {
    testQStringProperty("uniqueId", SIGNAL(uniqueIdChanged(QString)));
    testQStringProperty("title", SIGNAL(titleChanged(QString)));
    testQStringProperty("artist", SIGNAL(artistChanged(QString)));
    testQStringProperty("album", SIGNAL(albumChanged(QString)));
    testQStringProperty("artUrl", SIGNAL(artUrlChanged(QString)));
    testQStringProperty("duration", SIGNAL(durationChanged(double)), "0", "150", "300");
    testQStringProperty("isFavorite", SIGNAL(isFavoriteChanged(bool)), "false", "true", "false");
}

TEST_CASE("song can be converted to a string") {
    Song song;
    song.setTitle("Awesome song");
    song.setArtist("Awesome artist");
    song.setAlbum("Awesome album");
    REQUIRE(song.toString().toStdString() == "Song(title=\"Awesome song\", artist=\"Awesome artist\", "
        "album=\"Awesome album\")");
}