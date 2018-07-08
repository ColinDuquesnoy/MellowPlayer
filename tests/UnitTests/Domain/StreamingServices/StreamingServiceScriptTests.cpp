#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>
#include <QtTest/QSignalSpy>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

TEST_CASE("StreamingServiceScriptTests", "[UnitTest]")
{
    SECTION("StreamingServiceScript.code")
    {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.code().toStdString() == "code");
    }

    SECTION("StreamingServiceScript.path")
    {
        StreamingServiceScript script("code", "path");
        REQUIRE(script.path() == "path");
    }

    SECTION("StreamingServiceScript.setCode")
    {
        StreamingServiceScript script("code", "path");
        QSignalSpy spy(&script, SIGNAL(codeChanged(QString)));
        script.setCode("code");
        REQUIRE(spy.count() == 0);
        script.setCode("code2");
        REQUIRE(spy.count() == 1);
    }

    SECTION("StreamingServiceScript.isValid_validCode")
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
        StreamingServiceScript script(code, "path");
        REQUIRE(script.isValid());
    }

    SECTION("StreamingServiceScript.isValid_missUpdate")
    {
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

    SECTION("StreamingServiceScript.isValid_missPlay")
    {
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

    SECTION("StreamingServiceScript.isValid_missPause")
    {
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

    SECTION("StreamingServiceScript.isValid_missGoNext")
    {
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

    SECTION("StreamingServiceScript.isValid_missGoPrevious")
    {
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

    SECTION("StreamingServiceScript.isValid_missSetVolume")
    {
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

    SECTION("StreamingServiceScript.isValid_missAddToFavorites")
    {
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

    SECTION("StreamingServiceScript.isValid_missRemoveFromFavorites")
    {
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

    SECTION("StreamingServiceScript.isValid_missSeekToPositon")
    {
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

    SECTION("StreamingServiceScript.constants")
    {
        StreamingServiceScript script("", "");
        REQUIRE(!script.constants().isEmpty());
    }
}