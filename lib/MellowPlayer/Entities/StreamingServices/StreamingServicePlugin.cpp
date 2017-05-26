#include <memory>
#include <QtGui/QIcon>
#include <MellowPlayer/UseCases/Player/IPlayer.hpp>
#include "StreamingServicePlugin.hpp"
#include "StreamingServicePluginScript.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

StreamingServicePlugin::StreamingServicePlugin(const StreamingServicePluginMetadata& metadata,  const StreamingServiceStyle& style):
    metadata(metadata), style(style), script(make_unique<StreamingServicePluginScript>(metadata.script, metadata.scriptPath)) {
}

StreamingServicePlugin::~StreamingServicePlugin() = default;

const QString& StreamingServicePlugin::getAuthor() const {
    return metadata.author;
}

const QString& StreamingServicePlugin::getAuthorWebsite() const {
    return metadata.authorWebsite;
}

QString StreamingServicePlugin::getColor() const {
    if (QColor(metadata.color).isValid())
        return metadata.color;
    return "";
}

QString StreamingServicePlugin::getLogo() const {
    if (metadata.logoPath.isEmpty())
        return "";
    return "file://" + metadata.logoPath;
}

const QString& StreamingServicePlugin::getName() const {
    return metadata.name;
}

QString StreamingServicePlugin::getUrl() const {
    return metadata.url;
}

const QString& StreamingServicePlugin::getVersion() const {
    return metadata.version;
}

bool StreamingServicePlugin::isValid() const {
    return metadata.isValid() && script->isValid();
}

StreamingServicePluginScript* StreamingServicePlugin::getScript() const {
    return script.get();
}

const StreamingServiceStyle& StreamingServicePlugin::getStyle() const {
    return style;
}

bool StreamingServicePlugin::operator==(const StreamingServicePlugin& rhs) const {
    return getName() == rhs.getName();
}

bool StreamingServicePlugin::operator!=(const StreamingServicePlugin& rhs) const {
    return !operator==(rhs);
}
