#include <memory>
#include <QtGui/QIcon>
#include "StreamingService.hpp"
#include "Player.hpp"


USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

StreamingService::StreamingService(const PluginMetadata& metadata, IApplicationSettings& applicationSettings):
    logger(LoggingManager::instance().getLogger("StreamingService")),
    metadata(metadata), applicationSettings(applicationSettings),
    script(make_unique<PluginScript>(metadata.script, metadata.scriptPath)),
    player(make_unique<Player>(*this)) {

    if ((!metadata.isValid())) LOG_DEBUG(logger, "Invalid metadata, name or url is empty");
    if (!script->isValid()) LOG_DEBUG(logger, metadata.name.toStdString() << " invalid integration script");
}

StreamingService::~StreamingService() = default;

const QString& StreamingService::getAuthor() const {
    return metadata.author;
}

const QString& StreamingService::getAuthorWebsite() const {
    return metadata.authorWebsite;
}

QString StreamingService::getToolbarColor() const {
    if (QColor(metadata.color).isValid())
        return metadata.color;
    return "";
}

QString StreamingService::getLogo() const {
    if (metadata.logoPath.isEmpty())
        return "";
    return "file://" + metadata.logoPath;
}

const QString& StreamingService::getName() const {
    return metadata.name;
}

QString StreamingService::getUrl() const {
    QString customUrl = applicationSettings.getValue(getCustomUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? metadata.url : customUrl;
}

const QString StreamingService::getCustomUrlSettingsKey() const { return metadata.name + "/url"; }

const QString& StreamingService::getVersion() const {
    return metadata.version;
}

bool StreamingService::isValid() const {
    return metadata.isValid() && script->isValid();
}

void StreamingService::setCustomUrl(const QString& url) {
    if (url != getUrl()) {
        applicationSettings.setValue(getCustomUrlSettingsKey(), url);
        emit urlChanged(url);
    }
}

bool StreamingService::operator==(const StreamingService& rhs) const {
    return getName() == rhs.getName() && getUrl() == rhs.getUrl();
}

bool StreamingService::operator!=(const StreamingService& rhs) const {
    return !operator==(rhs);
}

PluginScript* StreamingService::getScript() {
    return script.get();
}

Player* StreamingService::getPlayer() {
    return player.get();
}
