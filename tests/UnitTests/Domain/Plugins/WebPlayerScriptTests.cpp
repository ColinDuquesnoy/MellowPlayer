#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

class FakeScript: public WebPlayerScript
{
public:
    FakeScript(QString code, QString path);
    void load() override { };
};

FakeScript::FakeScript(QString code, QString path)
{
    code_ = move(code);
    path_ = move(path);
}

TEST_CASE("WebPlayerScript")
{
    SECTION("WebPlayerScript.code")
    {
        FakeScript script("code", "path");
        REQUIRE(script.code() == "code");
    }

    SECTION("WebPlayerScript.path")
    {
        FakeScript script("code", "path");
        REQUIRE(script.path() == "path");
    }

    SECTION("WebPlayerScript.updateCode")
    {
        FakeScript script("code", "path");
        QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
        script.updateCode("code");
        REQUIRE(spy.count() == 0);
        script.updateCode("code2");
        REQUIRE(spy.count() == 1);
    }

    SECTION("WebPlayerScript.update")
    {
        FakeScript script("code", "path");
        REQUIRE(script.update() == "if (typeof update !== 'undefined') update();");
    }

    SECTION("WebPlayerScript.play")
    {
        FakeScript script("code", "path");
        REQUIRE(script.play() == "play();");
    }

    SECTION("WebPlayerScript.pause")
    {
        FakeScript script("code", "path");
        REQUIRE(script.pause() == "pause();");
    }

    SECTION("WebPlayerScript.next")
    {
        FakeScript script("code", "path");
        REQUIRE(script.next() == "goNext();");
    }

    SECTION("WebPlayerScript.previous")
    {
        FakeScript script("code", "path");
        REQUIRE(script.previous() == "goPrevious();");
    }

    SECTION("WebPlayerScript.setVolume")
    {
        FakeScript script("code", "path");
        REQUIRE(script.setVolume(95).toStdString() == "setVolume(95);");
    }

    SECTION("WebPlayerScript.addToFavorites")
    {
        FakeScript script("code", "path");
        REQUIRE(script.addToFavorites() == "addToFavorites();");
    }

    SECTION("WebPlayerScript.removeFromFavorites")
    {
        FakeScript script("code", "path");
        REQUIRE(script.removeFromFavorites() == "removeFromFavorites();");
    }

    SECTION("WebPlayerScript.seekToPosition")
    {
        FakeScript script("code", "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
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
        FakeScript script(code, "path");
        REQUIRE(!script.isValid());
    }

    SECTION("WebPlayerScript.constants")
    {
        FakeScript script("", "");
        REQUIRE(!script.constants().isEmpty());
    }
}
