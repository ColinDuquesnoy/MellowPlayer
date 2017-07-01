#include <catch.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServiceScript.hpp>
#include <QtTest/QSignalSpy>

USING_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

TEST_CASE("StreamingServiceScriptTests", "[UnitTest]") {
    SECTION("StreamingServiceScript.getCode") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.getCode().toStdString() == "code");
    }

    SECTION("StreamingServiceScript.getPath") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.getPath() == "path");
    }

    SECTION("StreamingServiceScript.setCode") {
        StreamingServiceScript script("code", "path");
        QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
        script.setCode("code");
        REQUIRE(spy.count() == 0);
        script.setCode("code2");
        REQUIRE(spy.count() == 1);
    }

    SECTION("StreamingServiceScript.update") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.update() == "if (typeof update !== 'undefined') update();");
    }

    SECTION("StreamingServiceScript.play") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.play() == "play();");
    }

    SECTION("StreamingServiceScript.pause") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.pause() == "pause();");
    }

    SECTION("StreamingServiceScript.next") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.next() == "goNext();");
    }

    SECTION("StreamingServiceScript.previous") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.previous() == "goPrevious();");
    }

    SECTION("StreamingServiceScript.setVolume") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.setVolume(95).toStdString() == "setVolume(95);");
    }

    SECTION("StreamingServiceScript.addToFavorites") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.addToFavorites() == "addToFavorites();");
    }

    SECTION("StreamingServiceScript.removeFromFavorites") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.removeFromFavorites() == "removeFromFavorites();");
    }

    SECTION("StreamingServiceScript.seekToPosition") {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.seekToPosition(95).toStdString() == "seekToPosition(95);");
    }


    SECTION("StreamingServiceScript.isValid_validCode") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missUpdate") {
        QString code = "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missPlay") {
        QString code = "function update\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missPause") {
        QString code = "function update\n"
                "function play\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missGoNext") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missGoPrevious") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missSetVolume") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missAddToFavorites") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missRemoveFromFavorites") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function seekToPosition\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missSeekToPositon") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n";
        StreamingServiceScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServiceScript.getConstants") {
        StreamingServiceScript script("", "");
        REQUIRE(!script.getConstants().isEmpty());
    }
}