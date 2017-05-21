#include "StreamingServicePluginScript.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)

StreamingServicePluginScript::StreamingServicePluginScript(const QString &code, const QString &path):
        QObject(), code(code), path(path) {

}

bool StreamingServicePluginScript::isValid() const {
    return code.contains("function update") && code.contains("function play") && (code.contains("function pause") &&
           code.contains("function goNext") && code.contains("function goPrevious") &&
           code.contains("function setVolume") && code.contains("function addToFavorites")) &&
           code.contains("function removeFromFavorites") && code.contains("function seekToPosition");
}

QString StreamingServicePluginScript::getCode() const {
    return code;
}

void StreamingServicePluginScript::setCode(const QString &value) {
    if (code == value)
        return;
    code = value;
    emit codeChanged(value);
}

const QString &StreamingServicePluginScript::getPath() const {
    return path;
}

QString StreamingServicePluginScript::update() const {
    return "if (typeof update !== 'undefined') update();";
}

QString StreamingServicePluginScript::play() const {
    return "play();";
}

QString StreamingServicePluginScript::pause() const {
    return "pause();";
}

QString StreamingServicePluginScript::next() const {
    return "goNext();";
}

QString StreamingServicePluginScript::previous() const {
    return "goPrevious();";
}

QString StreamingServicePluginScript::setVolume(double volume) const {
    return QString("setVolume(%1);").arg(volume);
}

QString StreamingServicePluginScript::addToFavorites() const {
    return "addToFavorites();";
}

QString StreamingServicePluginScript::removeFromFavorites() const {
    return "removeFromFavorites();";
}

QString StreamingServicePluginScript::seekToPosition(double position) const {
    return QString("seekToPosition(%1);").arg(position);
}

QString StreamingServicePluginScript::getConstants() const {
    return  "mellowplayer = {\n"
            "    PlaybackStatus: {\n"
            "        STOPPED: 0,\n"
            "        PLAYING: 1,\n"
            "        PAUSED: 2,\n"
            "        BUFFERING: 3\n"
            "    }\n"
            "};\n";
}
