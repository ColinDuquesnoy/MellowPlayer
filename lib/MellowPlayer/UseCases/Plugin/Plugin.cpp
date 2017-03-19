#include <memory>
#include <QtGui/QIcon>
#include "Plugin.hpp"
#include "../Player/Player.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

Plugin::Plugin(const PluginMetadata& metadata,  const PluginStyle& style):
    logger(LoggingManager::instance().getLogger("Plugin")),
    metadata(metadata), style(style), script(make_unique<PluginScript>(metadata.script, metadata.scriptPath)) {

    if ((!metadata.isValid())) LOG_DEBUG(logger, "Invalid metadata, name or url is empty");
    if (!script->isValid()) LOG_DEBUG(logger, metadata.name.toStdString() << " invalid integration script");
}

Plugin::~Plugin() = default;

const QString& Plugin::getAuthor() const {
    return metadata.author;
}

const QString& Plugin::getAuthorWebsite() const {
    return metadata.authorWebsite;
}

QString Plugin::getColor() const {
    if (QColor(metadata.color).isValid())
        return metadata.color;
    return "";
}

QString Plugin::getLogo() const {
    if (metadata.logoPath.isEmpty())
        return "";
    return "file://" + metadata.logoPath;
}

const QString& Plugin::getName() const {
    return metadata.name;
}

QString Plugin::getUrl() const {
    return metadata.url;
}

const QString& Plugin::getVersion() const {
    return metadata.version;
}

bool Plugin::isValid() const {
    return metadata.isValid() && script->isValid();
}

PluginScript* Plugin::getScript() const {
    return script.get();
}

const PluginStyle& Plugin::getStyle() const {
    return style;
}

bool Plugin::operator==(const Plugin& rhs) const {
    return getName() == rhs.getName() && getUrl() == rhs.getUrl();
}

bool Plugin::operator!=(const Plugin& rhs) const {
    return !operator==(rhs);
}
