#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include "StreamingServiceModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServiceModel::StreamingServiceModel(StreamingService& streamingService,
                                                         ISettingsProvider& settings,
                                                         Players& players,
                                                         QObject* parent) :
        QObject(parent),
        streamingService(streamingService),
        settingsProvider(settings),
        players(players) {
}

QString StreamingServiceModel::getColor() const {
    return streamingService.getColor();
}

QString StreamingServiceModel::getLogo() const {
    return streamingService.getLogo();
}

QString StreamingServiceModel::getName() const {
    return streamingService.getName();
}

Player* StreamingServiceModel::getPlayer() {
    return players.get(streamingService.getName()).get();
}

QString StreamingServiceModel::getUrl() const {
    QString customUrl = settingsProvider.getValue(getCustomUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? streamingService.getUrl() : customUrl;
}

QString StreamingServiceModel::getVersion() const {
    return streamingService.getVersion();
}

QString StreamingServiceModel::getAuthorName() const {
    return streamingService.getAuthor();
}

QString StreamingServiceModel::getAuthorWebsite() const {
    return streamingService.getAuthorWebsite();
}

bool StreamingServiceModel::operator==(const StreamingServiceModel& rhs) const {
    return streamingService == rhs.streamingService;
}

bool StreamingServiceModel::operator!=(const StreamingServiceModel& rhs) const {
    return !operator==(rhs);
}

StreamingService* StreamingServiceModel::getStreamingService() const {
    return &streamingService;
}

void StreamingServiceModel::setUrl(const QString& url) {
    if (url != getUrl()) {
        settingsProvider.setValue(getCustomUrlSettingsKey(), url);
        emit urlChanged(url);
    }
}

const QString StreamingServiceModel::getCustomUrlSettingsKey() const {
    return streamingService.getName() + "/url";
}

bool StreamingServiceModel::isRunning() const {
    return players.get(streamingService.getName()).get()->isRunning();
}
