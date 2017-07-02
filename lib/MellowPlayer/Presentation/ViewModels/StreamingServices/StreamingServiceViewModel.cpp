#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include "StreamingServiceViewModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServiceViewModel::StreamingServiceViewModel(StreamingService& streamingService,
                                                         ISettingsProvider& settings,
                                                         Players& players,
                                                         QObject* parent) :
        QObject(parent),
        streamingService(streamingService),
        settingsProvider(settings),
        players(players) {
}

QString StreamingServiceViewModel::getLogo() const {
    return streamingService.getLogo();
}

QString StreamingServiceViewModel::getName() const {
    return streamingService.getName();
}

Player* StreamingServiceViewModel::getPlayer() {
    return players.get(streamingService.getName()).get();
}

QString StreamingServiceViewModel::getUrl() const {
    QString customUrl = settingsProvider.getValue(getCustomUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? streamingService.getUrl() : customUrl;
}

QString StreamingServiceViewModel::getVersion() const {
    return streamingService.getVersion();
}

QString StreamingServiceViewModel::getAuthorName() const {
    return streamingService.getAuthor();
}

QString StreamingServiceViewModel::getAuthorWebsite() const {
    return streamingService.getAuthorWebsite();
}

bool StreamingServiceViewModel::operator==(const StreamingServiceViewModel& rhs) const {
    return streamingService == rhs.streamingService;
}

bool StreamingServiceViewModel::operator!=(const StreamingServiceViewModel& rhs) const {
    return !operator==(rhs);
}

StreamingService* StreamingServiceViewModel::getStreamingService() const {
    return &streamingService;
}

void StreamingServiceViewModel::setUrl(const QString& url) {
    if (url != getUrl()) {
        settingsProvider.setValue(getCustomUrlSettingsKey(), url);
        emit urlChanged(url);
    }
}

const QString StreamingServiceViewModel::getCustomUrlSettingsKey() const {
    return streamingService.getName() + "/url";
}

bool StreamingServiceViewModel::isRunning() const {
    return players.get(streamingService.getName()).get()->isRunning();
}
