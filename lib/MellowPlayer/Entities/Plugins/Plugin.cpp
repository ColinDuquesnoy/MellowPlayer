#include <memory>
#include "Plugin.hpp"
#include <QtGui/QIcon>
#include <QtCore/QSettings>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

Plugin::Plugin(const PluginMetadata &metadata) :
    logger(LoggingManager::instance().getLogger("Plugin")),
    metadata(metadata), script(make_unique<PluginScript>(metadata.script, metadata.scriptPath)) {

    if( (!metadata.isValid()))
        LOG_WARN(logger, "Invalid metadata, name or url is empty");

    if (!script->isValid())
        LOG_WARN(logger, metadata.name.toStdString() << " invalid integration script");
}

const QString &Plugin::getAuthor() const {
    return metadata.author;
}

const QString &Plugin::getAuthorWebsite() const {
    return metadata.authorWebsite;
}

QString Plugin::getToolbarColor() const {
    if(QColor(metadata.color).isValid())
        return metadata.color;
    return "";
}

QString Plugin::getLogo() const {
    if (metadata.logoPath.isEmpty())
        return "";
    return "file://" + metadata.logoPath;
}

const QString &Plugin::getName() const {
    return metadata.name;
}

QString Plugin::getUrl() const {
    QSettings settings;
    QString customUrl = settings.value(getCustomUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? metadata.url : customUrl;
}

const QString Plugin::getCustomUrlSettingsKey() const { return metadata.name + "/url"; }

const QString &Plugin::getVersion() const {
    return metadata.version;
}

PluginScript& Plugin::getScript() {
    return *script;
}

PluginScript *Plugin::getScriptPtr() {
    return &getScript();
}

bool Plugin::isValid() const {
    return metadata.isValid() && script->isValid();
}

void Plugin::setCustomUrl(const QString &url) {
    QSettings settings;
    if (url != getUrl()) {
        settings.setValue(getCustomUrlSettingsKey(), url);
        emit urlChanged(url);
    }
}

bool Plugin::operator==(const Plugin &rhs) const {
    return getName() == rhs.getName() && getUrl() == rhs.getUrl();
}

bool Plugin::operator!=(const Plugin &rhs) const {
    return !operator==(rhs);
}
