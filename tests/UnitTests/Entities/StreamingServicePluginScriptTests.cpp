#include <catch.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePluginScript.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

TEST_CASE("PluginScriptTests", "[UnitTest]") {
    SECTION("StreamingServicePluginScript.getCode") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.getCode().toStdString() == "code");
    }

    SECTION("StreamingServicePluginScript.getPath") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.getPath() == "path");
    }

    SECTION("StreamingServicePluginScript.setCode") {
        StreamingServicePluginScript script("code", "path");
        QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
        script.setCode("code");
        REQUIRE(spy.count() == 0);
        script.setCode("code2");
        REQUIRE(spy.count() == 1);
    }

    SECTION("StreamingServicePluginScript.update") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.update() == "if (typeof update !== 'undefined') update();");
    }

    SECTION("StreamingServicePluginScript.play") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.play() == "play();");
    }

    SECTION("StreamingServicePluginScript.pause") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.pause() == "pause();");
    }

    SECTION("StreamingServicePluginScript.next") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.next() == "goNext();");
    }

    SECTION("StreamingServicePluginScript.previous") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.previous() == "goPrevious();");
    }

    SECTION("StreamingServicePluginScript.setVolume") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.setVolume(95).toStdString() == "setVolume(95);");
    }

    SECTION("StreamingServicePluginScript.addToFavorites") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.addToFavorites() == "addToFavorites();");
    }

    SECTION("StreamingServicePluginScript.removeFromFavorites") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.removeFromFavorites() == "removeFromFavorites();");
    }

    SECTION("StreamingServicePluginScript.seekToPosition") {
        StreamingServicePluginScript script("code", "path");
        REQUIRE(script.seekToPosition(95).toStdString() == "seekToPosition(95);");
    }


    SECTION("StreamingServicePluginScript.isValid_validCode") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missUpdate") {
        QString code = "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missPlay") {
        QString code = "function update\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missPause") {
        QString code = "function update\n"
                "function play\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missGoNext") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missGoPrevious") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missSetVolume") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missAddToFavorites") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missRemoveFromFavorites") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function seekToPosition\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.isValid_missSeekToPositon") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n";
        StreamingServicePluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("StreamingServicePluginScript.getConstants") {
        StreamingServicePluginScript script("", "");
        REQUIRE(!script.getConstants().isEmpty());
    }
}