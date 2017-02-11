#include "PluginScript.hpp"

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)

PluginScript::PluginScript(const QString &code, const QString &path)
    :
    QObject(), logger(LoggingManager::instance().getLogger("PluginScript")), code(code), path(path) {

}

bool PluginScript::isValid() const {
    if (code.contains("function updatePlayerInfo")) {
        if (code.contains("function updateSongInfo")) {
            if (code.contains("function play")) {
                if (code.contains("function pause")) {
                    if (code.contains("function goNext")) {
                        if (code.contains("function goPrevious")) {
                            if (code.contains("function setVolume")) {
                                if (code.contains("function addToFavorites")) {
                                    if (code.contains("function removeFromFavorites")) {
                                        if (code.contains("function seekToPosition")) {
                                            return true;
                                        }
                                        else {
                                            LOG_WARN(logger, "Invalid script: 'seekToPosition' function not found");
                                        }
                                    }
                                    else {
                                        LOG_WARN(logger, "Invalid script: 'removeFromFavorites' function not found");
                                    }
                                }
                                else {
                                    LOG_WARN(logger, "Invalid script: 'addToFavorites' function not found");
                                }
                            }
                            else {
                                LOG_WARN(logger, "Invalid script: 'setVolume' function not found");
                            }
                        }
                        else {
                            LOG_WARN(logger, "Invalid script: 'goPrevious' function not found");
                        }
                    }
                    else {
                        LOG_WARN(logger, "Invalid script: 'goNext' function not found");
                    }
                }
                else {
                    LOG_WARN(logger, "Invalid script: 'pause' function not found");
                }
            }
            else {
                LOG_WARN(logger, "Invalid script: 'play' function not found");
            }
        }
        else {
            LOG_WARN(logger, "Invalid script: 'updateSongInfo' function not found");
        }
    }
    else {
        LOG_WARN(logger, "Invalid script: 'updatePlayerInfo' function not found");
    }
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
