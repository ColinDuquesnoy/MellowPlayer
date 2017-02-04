#include <catch.hpp>
#include <MellowPlayer/Entities/Plugins.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

TEST_CASE("PluginScript.getCode") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->getCode() == "code");
}

TEST_CASE("PluginScript.getPath") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->getPath() == "path");
}

TEST_CASE("PluginScript.setCode") {
    auto script = make_unique<PluginScript>("code", "path");
    QSignalSpy spy(script.get(), SIGNAL(codeChanged(QString)));
    script->setCode("code");
    REQUIRE(spy.count() == 0);
    script->setCode("code2");
    REQUIRE(spy.count() == 1);
}

TEST_CASE("PluginScript.updatePlayerInfo") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->updatePlayerInfo() == "updatePlayerInfo();");
}

TEST_CASE("PluginScript.updateSongInfo") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->updateSongInfo() == "updateSongInfo();");
}

TEST_CASE("PluginScript.play") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->play() == "play();");
}

TEST_CASE("PluginScript.pause") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->pause() == "pause();");
}

TEST_CASE("PluginScript.next") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->next() == "goNext();");
}

TEST_CASE("PluginScript.previous") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->previous() == "goPrevious();");
}

TEST_CASE("PluginScript.setVolume") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->setVolume(95).toStdString() == "setVolume(95);");
}

TEST_CASE("PluginScript.addToFavorites") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->addToFavorites() == "addToFavorites();");
}

TEST_CASE("PluginScript.removeFromFavorites") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->removeFromFavorites() == "removeFromFavorites();");
}

TEST_CASE("PluginScript.seekToPosition") {
    auto script = make_unique<PluginScript>("code", "path");
    REQUIRE(script->seekToPosition(95).toStdString() == "seekToPosition(95);");
}
