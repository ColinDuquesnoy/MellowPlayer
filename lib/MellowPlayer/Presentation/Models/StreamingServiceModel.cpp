#include <MellowPlayer/UseCases/Interfaces/IApplicationSettings.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include <MellowPlayer/UseCases/Services/PlayerService.hpp>
#include "StreamingServiceModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServiceModel::StreamingServiceModel(Plugin& plugin,
                                             IApplicationSettings& applicationSettings,
                                             PlayerService& playerService,
                                             QObject* parent) :
        QObject(parent),
        plugin(plugin),
        applicationSettings(applicationSettings),
        players(playerService) {
}
QString StreamingServiceModel::getColor() const {
    return plugin.getColor();
}

QString StreamingServiceModel::getLogo() const {
    return plugin.getLogo();
}

QString StreamingServiceModel::getName() const {
    return plugin.getName();
}

Player* StreamingServiceModel::getPlayer() {
    return players.get(plugin.getName()).get();
}

QString StreamingServiceModel::getUrl() const {
    QString customUrl = applicationSettings.getValue(getCustomUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? plugin.getUrl() : customUrl;
}

void StreamingServiceModel::setCustomUrl(const QString& url) {
    if (url != getUrl()) {
        applicationSettings.setValue(getCustomUrlSettingsKey(), url);
        emit urlChanged(url);
    }
}

bool StreamingServiceModel::operator==(const StreamingServiceModel& rhs) const {
    return plugin == rhs.plugin;
}

bool StreamingServiceModel::operator!=(const StreamingServiceModel& rhs) const {
    return !operator==(rhs);
}

Plugin* StreamingServiceModel::getPlugin() const {
    return &plugin;
}

const QString StreamingServiceModel::getCustomUrlSettingsKey() const {
    return plugin.getName() + "/url";
}
