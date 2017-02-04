#include "PluginScript.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)

PluginScript::PluginScript(const QString &code, const QString &path): code(code), path(path) {

}

bool PluginScript::isValid() const {
    return false;
}

const QString &PluginScript::getCode() const {
    return code;
}

void PluginScript::setCode(const QString &value) {
    if (code == value)
        return;
    code = value;
    emit codeChanged(value);
}

const QString &PluginScript::getPath() const {
    return path;
}

QString PluginScript::updatePlayerInfo() const {
    return "updatePlayerInfo();";
}

QString PluginScript::updateSongInfo() const {
    return "updateSongInfo();";
}

QString PluginScript::play() const {
    return "play();";
}

QString PluginScript::pause() const {
    return "pause();";
}

QString PluginScript::next() const {
    return "goNext();";
}

QString PluginScript::previous() const {
    return "goPrevious();";
}

QString PluginScript::setVolume(int volume) const {
    return QString("setVolume(%1);").arg(volume);
}

QString PluginScript::addToFavorites() const {
    return "addToFavorites();";
}

QString PluginScript::removeFromFavorites() const {
    return "removeFromFavorites();";
}

QString PluginScript::seekToPosition(int position) const {
    return QString("seekToPosition(%1);").arg(position);
}
