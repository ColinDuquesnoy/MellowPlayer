#include <QSet>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include "ListeningHistory.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)

ListeningHistory::ListeningHistory(IListeningHistoryDataProvider& model, IPlayer& player,
                                                 IWorkDispatcher& workDispatcher, Settings& settings):
        logger(LoggingManager::instance().getLogger("ListeningHistory")), dataProvider(model), player(player),
        workDispatcher(workDispatcher), isEnabledSetting(settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY)) {
    connect(&player, &IPlayer::currentSongChanged, this, &ListeningHistory::onCurrentSongChanged);
    connect(&player, &IPlayer::playbackStatusChanged, this, &ListeningHistory::onPlaybackStatusChanged);
    connect(&isEnabledSetting, &Setting::valueChanged, this, &ListeningHistory::onIsEnabledChanged);
}

void ListeningHistory::onPlaybackStatusChanged() {
    onCurrentSongChanged(player.getCurrentSong());
}

void ListeningHistory::onCurrentSongChanged(Song* song) {
    auto newEntry = ListeningHistoryEntry::fromData(song, player.getServiceName());
    workDispatcher.invoke([=]() mutable {
        addSong(song, newEntry);
    });
}

void ListeningHistory::initialize() {
    dataProvider.initialize();
    entries = this->dataProvider.getAll();
}

const QList<ListeningHistoryEntry>& ListeningHistory::getEntries() const {
    return entries;
}

int ListeningHistory::count() const {
    return getEntries().count();
}

void ListeningHistory::clear() {
    workDispatcher.invoke([=]() mutable {
        dataProvider.clear();
        updateRemovedEntries();
    });
}

void ListeningHistory::removeById(int entryId) {
    workDispatcher.invoke([=]() mutable {
        dataProvider.remove("id", QString("%1").arg(entryId));
        updateRemovedEntries();
    });
}

void ListeningHistory::removeByService(const QString& serviceName) {
    workDispatcher.invoke([=]() mutable {
        dataProvider.remove("serviceName", serviceName);
        updateRemovedEntries();
    });
}

void ListeningHistory::removeManyById(const QList<int> &ids) {
    workDispatcher.invoke([=]() mutable {
        dataProvider.removeMany(ids);
        updateRemovedEntries();
    });
}

void ListeningHistory::addSong(const Song* song, ListeningHistoryEntry& newEntry) {
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

void ListeningHistory::updateRemovedEntries() {
    auto removedEntries = entries.toSet().subtract(dataProvider.getAll().toSet()).toList();
    for (auto entry: removedEntries) {
        int index = entries.indexOf(entry);
        entries.removeAt(index);
        emit entryRemoved(entry.id);
    }
}

void ListeningHistory::onIsEnabledChanged() {
    if (!isEnabledSetting.getValue().toBool())
        clear();
}
