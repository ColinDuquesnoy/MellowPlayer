#include "StreamingServiceScript.hpp"

using namespace MellowPlayer::Application;

StreamingServiceScript::StreamingServiceScript(const QString &code, const QString &path)
        : QObject(), code(code), path(path)
{
}

bool StreamingServiceScript::isValid() const
{
    return code.contains("function update") && code.contains("function play")
    && (code.contains("function pause") && code.contains("function goNext") && code.contains("function goPrevious")
        && code.contains("function setVolume") && code.contains("function addToFavorites"))
    && code.contains("function removeFromFavorites") && code.contains("function seekToPosition");
}

QString StreamingServiceScript::getCode() const
{
    return code;
}

void StreamingServiceScript::setCode(const QString &value)
{
    if (code == value)
        return;
    code = value;
    emit codeChanged(value);
}

const QString &StreamingServiceScript::getPath() const
{
    return path;
}

QString StreamingServiceScript::update() const
{
    return "if (typeof update !== 'undefined') update();";
}

QString StreamingServiceScript::play() const
{
    return "play();";
}

QString StreamingServiceScript::pause() const
{
    return "pause();";
}

QString StreamingServiceScript::next() const
{
    return "goNext();";
}

QString StreamingServiceScript::previous() const
{
    return "goPrevious();";
}

QString StreamingServiceScript::setVolume(double volume) const
{
    return QString("setVolume(%1);").arg(volume);
}

QString StreamingServiceScript::addToFavorites() const
{
    return "addToFavorites();";
}

QString StreamingServiceScript::removeFromFavorites() const
{
    return "removeFromFavorites();";
}

QString StreamingServiceScript::seekToPosition(double position) const
{
    return QString("seekToPosition(%1);").arg(position);
}

QString StreamingServiceScript::getConstants() const
{
    return "mellowplayer = {\n"
           "    PlaybackStatus: {\n"
           "        STOPPED: 0,\n"
           "        PLAYING: 1,\n"
           "        PAUSED: 2,\n"
           "        BUFFERING: 3\n"
           "    }\n"
           "};\n";
}
