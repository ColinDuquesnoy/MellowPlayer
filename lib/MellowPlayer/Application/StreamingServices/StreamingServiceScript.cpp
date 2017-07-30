#include "StreamingServiceScript.hpp"

using namespace MellowPlayer::Application;

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

QString StreamingServiceScript::constants() const
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
