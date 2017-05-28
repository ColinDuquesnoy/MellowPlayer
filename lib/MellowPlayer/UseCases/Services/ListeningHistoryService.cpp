#include <QSet>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Player/IPlayer.hpp>
#include <MellowPlayer/UseCases/Interfaces/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/UseCases/Settings/Settings.hpp>
#include "ListeningHistoryService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

ListeningHistoryService::ListeningHistoryService(IListeningHistoryDataProvider& model, IPlayer& player,
                                                 IWorkDispatcher& workDispatcher, Settings& settings):
        logger(LoggingManager::instance().getLogger("ListeningHistoryService")), dataProvider(model), player(player),
        workDispatcher(workDispatcher), isEnabledSetting(settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY)) {
    connect(&player, &IPlayer::currentSongChanged, this, &ListeningHistoryService::onCurrentSongChanged);
    connect(&player, &IPlayer::playbackStatusChanged, this, &ListeningHistoryService::onPlaybackStatusChanged);
    connect(&isEnabledSetting, &Setting::valueChanged, this, &ListeningHistoryService::onIsEnabledChanged);
}

void ListeningHistoryService::onPlaybackStatusChanged() {
    onCurrentSongChanged(player.getCurrentSong());
}

void ListeningHistoryService::onCurrentSongChanged(Song* song) {
    auto newEntry = ListeningHistoryEntry::fromData(song, player.getServiceName());
    workDispatcher.invoke([=]() mutable {
        addSong(song, newEntry);
    });
}

void ListeningHistoryService::initialize() {
    dataProvider.initialize();
    entries = this->dataProvider.getAll();
}

const QList<ListeningHistoryEntry>& ListeningHistoryService::getEntries() const {
    return entries;
}

int ListeningHistoryService::count() const {
    return getEntries().count();
}

void ListeningHistoryService::clear() {
    workDispatcher.invoke([=]() mutable {
        dataProvider.clear();
        updateRemovedEntries();
    });
}

void ListeningHistoryService::removeById(int entryId) {
    workDispatcher.invoke([=]() mutable {
        dataProvider.remove("id", QString("%1").arg(entryId));
        updateRemovedEntries();
    });
}

void ListeningHistoryService::removeByService(const QString& serviceName) {
    workDispatcher.invoke([=]() mutable {
        dataProvider.remove("serviceName", serviceName);
        updateRemovedEntries();
    });
}

void ListeningHistoryService::removeManyById(const QList<int> &ids) {
    workDispatcher.invoke([=]() mutable {
        dataProvider.removeMany(ids);
        updateRemovedEntries();
    });
}

void ListeningHistoryService::addSong(const Song* song, ListeningHistoryEntry& newEntry) {
    if (!isEnabledSetting.getValue().toBool())
        return;

    auto previousEntry = previousEntryPerPlayer[player.getServiceName()];

    if (previousEntry.equals(newEntry) || !newEntry.isValid() ||
        player.getPlaybackStatus() != PlaybackStatus::Playing)
        return;

    newEntry.id = dataProvider.add(newEntry);
    entries.append(newEntry);emit
    entryAdded(newEntry);
    previousEntryPerPlayer[player.getServiceName()] = newEntry;
    LOG_DEBUG(logger, "new entry: " + song->toString() + ", id=" + QString("%1").arg(newEntry.id));
}

void ListeningHistoryService::updateRemovedEntries() {
    auto removedEntries = entries.toSet().subtract(dataProvider.getAll().toSet()).toList();
    for (auto entry: removedEntries) {
        int index = entries.indexOf(entry);
        entries.removeAt(index);
        emit entryRemoved(entry.id);
    }
}

void ListeningHistoryService::onIsEnabledChanged() {
    if (!isEnabledSetting.getValue().toBool())
        clear();
}
