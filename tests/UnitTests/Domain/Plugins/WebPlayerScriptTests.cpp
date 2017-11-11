#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>
#include "Fakes/FakeWebPlayerScript.hpp"

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

TEST_CASE("WebPlayerScript")
{
    SECTION("WebPlayerScript.code")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.code() == "code");
    }

    SECTION("WebPlayerScript.updateCode")
    {
        FakeWebPlayerScript script("code");
        QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
        script.updateCode("code");
        REQUIRE(spy.count() == 0);
        script.updateCode("code2");
        REQUIRE(spy.count() == 1);
    }

    SECTION("WebPlayerScript.update")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.update() == "if (typeof update !== 'undefined') update();");
    }

    SECTION("WebPlayerScript.play")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.play() == "play();");
    }

    SECTION("WebPlayerScript.pause")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.pause() == "pause();");
    }

    SECTION("WebPlayerScript.next")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.next() == "goNext();");
    }

    SECTION("WebPlayerScript.previous")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.previous() == "goPrevious();");
    }

    SECTION("WebPlayerScript.setVolume")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.setVolume(95).toStdString() == "setVolume(95);");
    }

    SECTION("WebPlayerScript.addToFavorites")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.addToFavorites() == "addToFavorites();");
    }

    SECTION("WebPlayerScript.removeFromFavorites")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.removeFromFavorites() == "removeFromFavorites();");
    }

    SECTION("WebPlayerScript.seekToPosition")
    {
        FakeWebPlayerScript script("code");
        REQUIRE(script.seekToPosition(95).toStdString() == "seekToPosition(95);");
    }

    SECTION("WebPlayerScript.isValid_validCode")
    {
        QString code = "function update\n"
                       "function play\n"
                       "function pause\n"
                       "function goNext\n"
                       "function goPrevious\n"
                       "function setVolume\n"
                       "function addToFavorites\n"
                       "function removeFromFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missUpdate")
    {
        QString code = "function play\n"
                       "function pause\n"
                       "function goNext\n"
                       "function goPrevious\n"
                       "function setVolume\n"
                       "function addToFavorites\n"
                       "function removeFromFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missPlay")
    {
        QString code = "function update\n"
                       "function pause\n"
                       "function goNext\n"
                       "function goPrevious\n"
                       "function setVolume\n"
                       "function addToFavorites\n"
                       "function removeFromFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missPause")
    {
        QString code = "function update\n"
                       "function play\n"
                       "function goNext\n"
                       "function goPrevious\n"
                       "function setVolume\n"
                       "function addToFavorites\n"
                       "function removeFromFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missGoNext")
    {
        QString code = "function update\n"
                       "function play\n"
                       "function pause\n"
                       "function goPrevious\n"
                       "function setVolume\n"
                       "function addToFavorites\n"
                       "function removeFromFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missGoPrevious")
    {
        QString code = "function update\n"
                       "function play\n"
                       "function pause\n"
                       "function goNext\n"
                       "function setVolume\n"
                       "function addToFavorites\n"
                       "function removeFromFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missSetVolume")
    {
        QString code = "function update\n"
                       "function play\n"
                       "function pause\n"
                       "function goNext\n"
                       "function goPrevious\n"
                       "function addToFavorites\n"
                       "function removeFromFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missAddToFavorites")
    {
        QString code = "function update\n"
                       "function play\n"
                       "function pause\n"
                       "function goNext\n"
                       "function goPrevious\n"
                       "function setVolume\n"
                       "function removeFromFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missRemoveFromFavorites")
    {
        QString code = "function update\n"
                       "function play\n"
                       "function pause\n"
                       "function goNext\n"
                       "function goPrevious\n"
                       "function setVolume\n"
                       "function addToFavorites\n"
                       "function seekToPosition\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.isValid_missSeekToPositon")
    {
        QString code = "function update\n"
                       "function play\n"
                       "function pause\n"
                       "function goNext\n"
                       "function goPrevious\n"
                       "function setVolume\n"
                       "function addToFavorites\n"
                       "function removeFromFavorites\n";
        FakeWebPlayerScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.constants")
    {
        FakeWebPlayerScript script("");
        REQUIRE(!script.constants().isEmpty());
    }
}
