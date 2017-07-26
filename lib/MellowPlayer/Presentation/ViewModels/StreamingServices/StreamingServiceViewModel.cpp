#include "StreamingServiceViewModel.hpp"
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

StreamingServiceViewModel::StreamingServiceViewModel(StreamingService& streamingService, ISettingsProvider& settings, Players& players,
                                                     QObject* parent)
        : QObject(parent), streamingService(streamingService), settingsProvider(settings), player(players.get(streamingService.getName()))
{
}

QString StreamingServiceViewModel::getLogo() const
{
    return streamingService.getLogo();
}

QString StreamingServiceViewModel::getName() const
{
    return streamingService.getName();
}

Player* StreamingServiceViewModel::getPlayer()
{
    return player.get();
}

QString StreamingServiceViewModel::getUrl() const
{
    QString customUrl = settingsProvider.getValue(getCustomUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? streamingService.getUrl() : customUrl;
}

QString StreamingServiceViewModel::getVersion() const
{
    return streamingService.getVersion();
}

QString StreamingServiceViewModel::getAuthorName() const
{
    return streamingService.getAuthor();
}

QString StreamingServiceViewModel::getAuthorWebsite() const
{
    return streamingService.getAuthorWebsite();
}

bool StreamingServiceViewModel::operator==(const StreamingServiceViewModel& rhs) const
{
    return streamingService == rhs.streamingService;
}

bool StreamingServiceViewModel::operator!=(const StreamingServiceViewModel& rhs) const
{
    return !operator==(rhs);
}

StreamingService* StreamingServiceViewModel::getStreamingService() const
{
    return &streamingService;
}

int StreamingServiceViewModel::getSortOrder() const
{
    return settingsProvider.getValue(getSortOrderSettingsKey(), "-1").toInt();
}

void StreamingServiceViewModel::setSortOrder(int newOrder)
{
    settingsProvider.setValue(getSortOrderSettingsKey(), newOrder);
    emit sortOrderChanged();
}

bool StreamingServiceViewModel::isEnabled() const
{
    return settingsProvider.getValue(getIsEnabledSettingsKey(), "true").toBool();
}

void StreamingServiceViewModel::setEnabled(bool enabled)
{
    if (enabled != isEnabled()) {
        settingsProvider.setValue(getIsEnabledSettingsKey(), enabled);
        emit isEnabledChanged();

        if (!enabled) {
            player->stop();
            player->suspend();
            setSortOrder(255);
        }
    }
}

void StreamingServiceViewModel::setUrl(const QString& url)
{
    if (url != getUrl()) {
        settingsProvider.setValue(getCustomUrlSettingsKey(), url);
        emit urlChanged(url);
    }
}

QString StreamingServiceViewModel::getCustomUrlSettingsKey() const
{
    return streamingService.getName() + "/url";
}

bool StreamingServiceViewModel::isRunning() const
{
    return player->isRunning();
}

QString StreamingServiceViewModel::getSortOrderSettingsKey() const
{
    return streamingService.getName() + "/sortOrder";
}

QString StreamingServiceViewModel::getIsEnabledSettingsKey() const
{
    return streamingService.getName() + "/isEnabled";
}
