#include <catch.hpp>
#include <MellowPlayer/UseCases.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

TEST_CASE("PluginScript.getCode") {
    PluginScript script("code", "path");
    REQUIRE(script.getCode().toStdString() == "code");
}

TEST_CASE("PluginScript.getPath") {
    PluginScript script("code", "path");
    REQUIRE(script.getPath() == "path");
}

TEST_CASE("PluginScript.setCode") {
    PluginScript script("code", "path");
    QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
    script.setCode("code");
    REQUIRE(spy.count() == 0);
    script.setCode("code2");
    REQUIRE(spy.count() == 1);
}

TEST_CASE("PluginScript.update") {
    PluginScript script("code", "path");
    REQUIRE(script.update() == "if (typeof update !== 'undefined') update();");
}

TEST_CASE("PluginScript.play") {
    PluginScript script("code", "path");
    REQUIRE(script.play() == "play();");
}

TEST_CASE("PluginScript.pause") {
    PluginScript script("code", "path");
    REQUIRE(script.pause() == "pause();");
}

TEST_CASE("PluginScript.next") {
    PluginScript script("code", "path");
    REQUIRE(script.next() == "goNext();");
}

TEST_CASE("PluginScript.previous") {
    PluginScript script("code", "path");
    REQUIRE(script.previous() == "goPrevious();");
}

TEST_CASE("PluginScript.setVolume") {
    PluginScript script("code", "path");
    REQUIRE(script.setVolume(95).toStdString() == "setVolume(95);");
}

TEST_CASE("PluginScript.addToFavorites") {
    PluginScript script("code", "path");
    REQUIRE(script.addToFavorites() == "addToFavorites();");
}

TEST_CASE("PluginScript.removeFromFavorites") {
    PluginScript script("code", "path");
    REQUIRE(script.removeFromFavorites() == "removeFromFavorites();");
}

TEST_CASE("PluginScript.seekToPosition") {
    PluginScript script("code", "path");
    REQUIRE(script.seekToPosition(95).toStdString() == "seekToPosition(95);");
}


TEST_CASE("PluginScript.isValid_validCode") {
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

TEST_CASE("PluginScript.isValid_missUpdate") {
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

TEST_CASE("PluginScript.isValid_missPlay") {
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

TEST_CASE("PluginScript.isValid_missPause") {
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

TEST_CASE("PluginScript.isValid_missGoNext") {
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

TEST_CASE("PluginScript.isValid_missGoPrevious") {
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

TEST_CASE("PluginScript.isValid_missSetVolume") {
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

TEST_CASE("PluginScript.isValid_missAddToFavorites") {
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

TEST_CASE("PluginScript.isValid_missRemoveFromFavorites") {
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

TEST_CASE("PluginScript.isValid_missSeekToPositon") {
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

TEST_CASE("PluginScript.getConstants") {
    PluginScript script("", "");
    REQUIRE(!script.getConstants().isEmpty());
}