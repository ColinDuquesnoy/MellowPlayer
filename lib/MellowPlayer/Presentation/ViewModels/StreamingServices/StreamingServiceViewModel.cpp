#include "StreamingServiceViewModel.hpp"
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

StreamingServiceViewModel::StreamingServiceViewModel(StreamingService& streamingService, 
                                                     ISettingsProvider& settings,
                                                     IUserScriptFactory& factory,
                                                     Players& players,
                                                     QObject* parent) : 
        QObject(parent), 
        streamingService_(streamingService), 
        settingsProvider_(settings), 
        player_(players.get(streamingService.name())),
        userScriptsViewModel_(streamingService.name(), factory, settings, this)
{
    
}

QString StreamingServiceViewModel::logo() const
{
    return streamingService_.logo();
}

QString StreamingServiceViewModel::name() const
{
    return streamingService_.name();
}

Player* StreamingServiceViewModel::player()
{
    return player_.get();
}

QString StreamingServiceViewModel::url() const
{
    QString customUrl = settingsProvider_.value(customUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? streamingService_.url() : customUrl;
}

QString StreamingServiceViewModel::version() const
{
    return streamingService_.version();
}

QString StreamingServiceViewModel::authorName() const
{
    return streamingService_.author();
}

QString StreamingServiceViewModel::authorWebsite() const
{
    return streamingService_.authorWebsite();
}

bool StreamingServiceViewModel::operator==(const StreamingServiceViewModel& rhs) const
{
    return streamingService_ == rhs.streamingService_;
}

bool StreamingServiceViewModel::operator!=(const StreamingServiceViewModel& rhs) const
{
    return !operator==(rhs);
}

StreamingService* StreamingServiceViewModel::streamingService() const
{
    return &streamingService_;
}

int StreamingServiceViewModel::sortOrder() const
{
    return settingsProvider_.value(sortOrderSettingsKey(), "-1").toInt();
}

void StreamingServiceViewModel::setSortOrder(int newOrder)
{
    settingsProvider_.setValue(sortOrderSettingsKey(), newOrder);
    emit sortOrderChanged();
}

bool StreamingServiceViewModel::isEnabled() const
{
    return settingsProvider_.value(isEnabledSettingsKey(), "true").toBool();
}

void StreamingServiceViewModel::setEnabled(bool enabled)
{
    if (enabled != isEnabled()) {
        settingsProvider_.setValue(isEnabledSettingsKey(), enabled);
        emit isEnabledChanged();

        if (!enabled) {
            player_->stop();
            player_->suspend();
            setSortOrder(255);
        }
    }
}

void StreamingServiceViewModel::setUrl(const QString& newUrl)
{
    if (newUrl != url()) {
        settingsProvider_.setValue(customUrlSettingsKey(), newUrl);
        emit urlChanged(newUrl);
    }
}

QString StreamingServiceViewModel::customUrlSettingsKey() const
{
    return streamingService_.name() + "/url";
}

bool StreamingServiceViewModel::isRunning() const
{
    return player_->isRunning();
}

QString StreamingServiceViewModel::sortOrderSettingsKey() const
{
    return streamingService_.name() + "/sortOrder";
}

QString StreamingServiceViewModel::isEnabledSettingsKey() const
{
    return streamingService_.name() + "/isEnabled";
}

QObject* StreamingServiceViewModel::userScripts()
{
    return &userScriptsViewModel_;
}
