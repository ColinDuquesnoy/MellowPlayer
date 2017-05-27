#include <MellowPlayer/UseCases/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/UseCases/Services/PlayerService.hpp>
#include "StreamingServicePluginModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicePluginModel::StreamingServicePluginModel(StreamingServicePlugin& plugin,
                                             ISettingsProvider& settings,
                                             PlayerService& playerService,
                                             QObject* parent) :
        QObject(parent),
        plugin(plugin),
        settingsProvider(settings),
        players(playerService) {
}
QString StreamingServicePluginModel::getColor() const {
    return plugin.getColor();
}

QString StreamingServicePluginModel::getLogo() const {
    return plugin.getLogo();
}

QString StreamingServicePluginModel::getName() const {
    return plugin.getName();
}

Player* StreamingServicePluginModel::getPlayer() {
    return players.get(plugin.getName()).get();
}

QString StreamingServicePluginModel::getUrl() const {
    QString customUrl = settingsProvider.getValue(getCustomUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? plugin.getUrl() : customUrl;
}

QString StreamingServicePluginModel::getVersion() const {
    return plugin.getVersion();
}

QString StreamingServicePluginModel::getAuthorName() const {
    return plugin.getAuthor();
}

QString StreamingServicePluginModel::getAuthorWebsite() const {
    return plugin.getAuthorWebsite();
}

bool StreamingServicePluginModel::operator==(const StreamingServicePluginModel& rhs) const {
    return plugin == rhs.plugin;
}

bool StreamingServicePluginModel::operator!=(const StreamingServicePluginModel& rhs) const {
    return !operator==(rhs);
}

StreamingServicePlugin* StreamingServicePluginModel::getPlugin() const {
    return &plugin;
}

void StreamingServicePluginModel::setUrl(const QString& url) {
    if (url != getUrl()) {
        settingsProvider.setValue(getCustomUrlSettingsKey(), url);
        emit urlChanged(url);
    }
}

const QString StreamingServicePluginModel::getCustomUrlSettingsKey() const {
    return plugin.getName() + "/url";
}