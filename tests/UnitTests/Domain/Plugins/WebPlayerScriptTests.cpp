#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

class FakeScript: public WebPlayerScript
{
public:
    FakeScript(QString code);
    void load() override { };
};

FakeScript::FakeScript(QString code)
{
    code_ = move(code);
}

TEST_CASE("WebPlayerScript")
{
    SECTION("WebPlayerScript.code")
    {
        FakeScript script("code");
        REQUIRE(script.code() == "code");
    }

    SECTION("WebPlayerScript.updateCode")
    {
        FakeScript script("code");
        QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
        script.updateCode("code");
        REQUIRE(spy.count() == 0);
        script.updateCode("code2");
        REQUIRE(spy.count() == 1);
    }

    SECTION("WebPlayerScript.update")
    {
        FakeScript script("code");
        REQUIRE(script.update() == "if (typeof update !== 'undefined') update();");
    }

    SECTION("WebPlayerScript.play")
    {
        FakeScript script("code");
        REQUIRE(script.play() == "play();");
    }

    SECTION("WebPlayerScript.pause")
    {
        FakeScript script("code");
        REQUIRE(script.pause() == "pause();");
    }

    SECTION("WebPlayerScript.next")
    {
        FakeScript script("code");
        REQUIRE(script.next() == "goNext();");
    }

    SECTION("WebPlayerScript.previous")
    {
        FakeScript script("code");
        REQUIRE(script.previous() == "goPrevious();");
    }

    SECTION("WebPlayerScript.setVolume")
    {
        FakeScript script("code");
        REQUIRE(script.setVolume(95).toStdString() == "setVolume(95);");
    }

    SECTION("WebPlayerScript.addToFavorites")
    {
        FakeScript script("code");
        REQUIRE(script.addToFavorites() == "addToFavorites();");
    }

    SECTION("WebPlayerScript.removeFromFavorites")
    {
        FakeScript script("code");
        REQUIRE(script.removeFromFavorites() == "removeFromFavorites();");
    }

    SECTION("WebPlayerScript.seekToPosition")
    {
        FakeScript script("code");
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
        FakeScript script(code);
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
        FakeScript script(code);
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
        FakeScript script(code);
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
        FakeScript script(code);
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
        FakeScript script(code);
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
        FakeScript script(code);
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
        FakeScript script(code);
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
        FakeScript script(code);
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
        FakeScript script(code);
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
        FakeScript script(code);
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.constants")
    {
        FakeScript script("");
        REQUIRE(!script.constants().isEmpty());
    }
}
