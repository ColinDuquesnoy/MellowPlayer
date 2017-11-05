#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

TEST_CASE("WebPlayerScript")
{
    SECTION("WebPlayerScript.code")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.code() == "code");
    }

    SECTION("WebPlayerScript.path")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.path() == "path");
    }

    SECTION("WebPlayerScript.updateCode")
    {
        WebPlayerScript script("code", "path");
        QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
        script.updateCode("code");
        REQUIRE(spy.count() == 0);
        script.updateCode("code2");
        REQUIRE(spy.count() == 1);
    }

    SECTION("WebPlayerScript.update")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.update() == "if (typeof update !== 'undefined') update();");
    }

    SECTION("WebPlayerScript.play")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.play() == "play();");
    }

    SECTION("WebPlayerScript.pause")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.pause() == "pause();");
    }

    SECTION("WebPlayerScript.next")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.next() == "goNext();");
    }

    SECTION("WebPlayerScript.previous")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.previous() == "goPrevious();");
    }

    SECTION("WebPlayerScript.setVolume")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.setVolume(95).toStdString() == "setVolume(95);");
    }

    SECTION("WebPlayerScript.addToFavorites")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.addToFavorites() == "addToFavorites();");
    }

    SECTION("WebPlayerScript.removeFromFavorites")
    {
        WebPlayerScript script("code", "path");
        REQUIRE(script.removeFromFavorites() == "removeFromFavorites();");
    }

    SECTION("WebPlayerScript.seekToPosition")
    {
        WebPlayerScript script("code", "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
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
        WebPlayerScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.constants")
    {
        WebPlayerScript script("", "");
        REQUIRE(!script.constants().isEmpty());
    }
}
