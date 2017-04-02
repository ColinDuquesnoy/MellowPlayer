#include <catch.hpp>
#include <MellowPlayer/Entities/PluginScript.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

TEST_CASE("PluginScriptTests") {
    SECTION("PluginScript.getCode") {
        PluginScript script("code", "path");
        REQUIRE(script.getCode().toStdString() == "code");
    }

    SECTION("PluginScript.getPath") {
        PluginScript script("code", "path");
        REQUIRE(script.getPath() == "path");
    }

    SECTION("PluginScript.setCode") {
        PluginScript script("code", "path");
        QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
        script.setCode("code");
        REQUIRE(spy.count() == 0);
        script.setCode("code2");
        REQUIRE(spy.count() == 1);
    }

    SECTION("PluginScript.update") {
        PluginScript script("code", "path");
        REQUIRE(script.update() == "if (typeof update !== 'undefined') update();");
    }

    SECTION("PluginScript.play") {
        PluginScript script("code", "path");
        REQUIRE(script.play() == "play();");
    }

    SECTION("PluginScript.pause") {
        PluginScript script("code", "path");
        REQUIRE(script.pause() == "pause();");
    }

    SECTION("PluginScript.next") {
        PluginScript script("code", "path");
        REQUIRE(script.next() == "goNext();");
    }

    SECTION("PluginScript.previous") {
        PluginScript script("code", "path");
        REQUIRE(script.previous() == "goPrevious();");
    }

    SECTION("PluginScript.setVolume") {
        PluginScript script("code", "path");
        REQUIRE(script.setVolume(95).toStdString() == "setVolume(95);");
    }

    SECTION("PluginScript.addToFavorites") {
        PluginScript script("code", "path");
        REQUIRE(script.addToFavorites() == "addToFavorites();");
    }

    SECTION("PluginScript.removeFromFavorites") {
        PluginScript script("code", "path");
        REQUIRE(script.removeFromFavorites() == "removeFromFavorites();");
    }

    SECTION("PluginScript.seekToPosition") {
        PluginScript script("code", "path");
        REQUIRE(script.seekToPosition(95).toStdString() == "seekToPosition(95);");
    }


    SECTION("PluginScript.isValid_validCode") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(script.isValid());
    }

    SECTION("PluginScript.isValid_missUpdate") {
        QString code = "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.isValid_missPlay") {
        QString code = "function update\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.isValid_missPause") {
        QString code = "function update\n"
                "function play\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.isValid_missGoNext") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.isValid_missGoPrevious") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.isValid_missSetVolume") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.isValid_missAddToFavorites") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function removeFromFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.isValid_missRemoveFromFavorites") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function seekToPosition\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.isValid_missSeekToPositon") {
        QString code = "function update\n"
                "function play\n"
                "function pause\n"
                "function goNext\n"
                "function goPrevious\n"
                "function setVolume\n"
                "function addToFavorites\n"
                "function removeFromFavorites\n";
        PluginScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("PluginScript.getConstants") {
        PluginScript script("", "");
        REQUIRE(!script.getConstants().isEmpty());
    }
}