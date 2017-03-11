#include <memory>
#include <QtGui/QIcon>
#include "Plugin.hpp"
#include "MellowPlayer/UseCases/Player/Player.hpp"


USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

Plugin::Plugin(const PluginMetadata& metadata):
    logger(LoggingManager::instance().getLogger("Plugin")),
    metadata(metadata), script(make_unique<PluginScript>(metadata.script, metadata.scriptPath)) {

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



bool Plugin::operator==(const Plugin& rhs) const {
    return getName() == rhs.getName() && getUrl() == rhs.getUrl();
}

bool Plugin::operator!=(const Plugin& rhs) const {
    return !operator==(rhs);
}

PluginScript* Plugin::getScript() const {
    return script.get();
}
