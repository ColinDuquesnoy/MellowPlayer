#include <QtConcurrent>
#include <QtCore/QThreadPool>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Player/IPlayer.hpp>
#include "IListeningHistoryDataProvider.hpp"
#include "ListeningHistory.hpp"


USE_MELLOWPLAYER_NAMESPACE(UseCases)

ListeningHistory::ListeningHistory(IListeningHistoryDataProvider& model, IPlayer& player):
        logger(LoggingManager::instance().getLogger("ListeningHistory")), model(model), player(player) {
    connect(&player, &IPlayer::currentSongChanged, this, &ListeningHistory::onCurrentSongChanged);
    connect(&player, &IPlayer::playbackStatusChanged, this, &ListeningHistory::onPlaybackStatusChanged);

    entries = this->model.getAll();
}

void ListeningHistory::onPlaybackStatusChanged() {
    onCurrentSongChanged(player.getCurrentSong());
}

void ListeningHistory::onCurrentSongChanged(Song* song) {
    auto newEntry = ListeningHistoryEntry::fromData(song, player.getServiceName());
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() mutable {
        QMutexLocker mutexLocker(&mutex);
        auto previousEntry = previousEntryPerPlayer[player.getServiceName()];

        if (previousEntry.equals(newEntry) || !newEntry.isValid() ||
            player.getPlaybackStatus() != PlaybackStatus::Playing)
            return;

        newEntry.id = model.add(newEntry);
        entries.append(newEntry);
        emit entryAdded(newEntry);
        previousEntryPerPlayer[player.getServiceName()] = newEntry;
        LOG_DEBUG(logger, "new entry: " + song->toString() + ", id=" + QString("%1").arg(newEntry.id));
    });
}

const QList<ListeningHistoryEntry>& ListeningHistory::getEntries() const {
    return entries;
}

void ListeningHistory::clear() {
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() mutable {
        QMutexLocker mutexLocker(&mutex);
        model.clear();
        entries.clear();
        emit entriesCleared();
    });
}

void ListeningHistory::removeById(int entryId) {
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() mutable {
        QMutexLocker mutexLocker(&mutex);
        model.remove("id", QString("%1").arg(entryId));
        auto entry = entries.toSet().subtract(model.getAll().toSet()).toList().first();
        int index = entries.indexOf(entry);
        entries.removeAt(index);
        emit entryRemoved(index);
    });
}

void ListeningHistory::removeByService(const QString& serviceName) {
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() mutable {
        QMutexLocker mutexLocker(&mutex);
        model.remove("serviceName", serviceName);

        for (auto entry: entries.toSet().subtract(model.getAll().toSet()).toList()) {
            int index = entries.indexOf(entry);
            entries.removeAt(index);
            emit entryRemoved(index);
        }
    });
}
