#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>

using namespace MellowPlayer::Domain;

StreamingServiceScript::StreamingServiceScript(const QString& code, const QString& path) : QObject(), code_(code), path_(path)
{
}

bool StreamingServiceScript::isValid() const
{
    return code_.contains("function update") && code_.contains("function play")
    && (code_.contains("function pause") && code_.contains("function goNext") && code_.contains("function goPrevious")
        && code_.contains("function setVolume") && code_.contains("function addToFavorites"))
    && code_.contains("function removeFromFavorites") && code_.contains("function seekToPosition");
}

QString StreamingServiceScript::code() const
{
    return code_;
}

void StreamingServiceScript::setCode(const QString& value)
{
    if (code_ == value)
        return;
    code_ = value;
    emit codeChanged(value);
}

const QString& StreamingServiceScript::path() const
{
    return path_;
}

QString StreamingServiceScript::constants() const
{
    return "mellowplayer = {\n"
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
           "}";
}
