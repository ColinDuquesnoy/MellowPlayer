#include "WebPlayerScript.hpp"

using namespace MellowPlayer::Domain;

WebPlayerScript::WebPlayerScript()
        : QObject(),
          constants_(
                "mellowplayer = {\n"
                "    PlaybackStatus: {\n"
                "        STOPPED: 0,\n"
                "        PLAYING: 1,\n"
                "        PAUSED: 2,\n"
                "        BUFFERING: 3\n"
                "    }\n"
                "};\n"
                "function getHashCode(s) {\n"
                "    return s.split(\"\").reduce(function(a, b) {\n"
                "        a = ((a << 5) - a) + b.charCodeAt(0);\n"
                "        return a & a\n"
                "    }, 0);\n"
                "}\n"
                "function toSeconds(string) {\n"
                "    try {\n"
                "        var dtimes = string.split(\":\");\n"
                "\n"
                "        if (dtimes.length === 3) {\n"
                "            var dhours = dtimes[0];\n"
                "            var dminutes = dtimes[1];\n"
                "            var dseconds = dtimes[2];\n"
                "            var duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60) + (parseInt(dhours, 10) * 60 * 60);\n"
                "        }\n"
                "        else {\n"
                "            var dminutes = dtimes[0];\n"
                "            var dseconds = dtimes[1];\n"
                "            var duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);\n"
                "        }\n"
                "\n"
                "    } catch (e) {\n"
                "        var duration = 0;\n"
                "    }\n"
                "\n"
                "    return duration\n"
                "}")
{
}

bool WebPlayerScript::isValid() const
{
    return code_.contains("function update") && code_.contains("function play")
    && (code_.contains("function pause") && code_.contains("function goNext") && code_.contains("function goPrevious")
        && code_.contains("function setVolume") && code_.contains("function addToFavorites"))
    && code_.contains("function removeFromFavorites") && code_.contains("function seekToPosition");
}

QString WebPlayerScript::update() const
{
    return "if (typeof update !== 'undefined') update();";
}

QString WebPlayerScript::play() const
{
    return "play();";
}

QString WebPlayerScript::pause() const
{
    return "pause();";
}

QString WebPlayerScript::next() const
{
    return "goNext();";
}

QString WebPlayerScript::previous() const
{
    return "goPrevious();";
}

QString WebPlayerScript::setVolume(double volume) const
{
    return QString("setVolume(%1);").arg(volume);
}

QString WebPlayerScript::addToFavorites() const
{
    return "addToFavorites();";
}

QString WebPlayerScript::removeFromFavorites() const
{
    return "removeFromFavorites();";
}

QString WebPlayerScript::seekToPosition(double position) const
{
    return QString("seekToPosition(%1);").arg(position);
}
