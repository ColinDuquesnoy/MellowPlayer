#include "ListeningHistory.hpp"
#include <QDateTime>
#include <QSet>
#include <QVariant>
#include <algorithm>
#include <MellowPlayer/Application/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/TimeLimits.hpp>
#include <MellowPlayer/Application/IWorkDispatcher.hpp>
#include <MellowPlayer/Application/Logging/ILogger.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Application/Player/Song.hpp>
#include <MellowPlayer/Application/Settings/SettingKey.hpp>

#define DELAY 5000

using namespace MellowPlayer::Application;

ListeningHistory::ListeningHistory(IListeningHistoryDataProvider& model, IPlayer& player, IWorkDispatcher& workDispatcher, Settings& settings)
        : logger(LoggingManager::logger("ListeningHistory")),
          dataProvider(model),
          player(player),
          workDispatcher(workDispatcher),
          isEnabledSetting(settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY)),
          limitSetting(settings.get(SettingKey::PRIVACY_LISTENING_HISTORY_LIMIT))
{
    connect(&player, &IPlayer::currentSongChanged, this, &ListeningHistory::onCurrentSongChanged);
    connect(&player, &IPlayer::playbackStatusChanged, this, &ListeningHistory::onPlaybackStatusChanged);
    connect(&isEnabledSetting, &Setting::valueChanged, this, &ListeningHistory::onIsEnabledChanged);
    connect(&limitSetting, &Setting::valueChanged, this, &ListeningHistory::clearOutdatedEntries);
}

void ListeningHistory::onPlaybackStatusChanged()
{
    onCurrentSongChanged(player.currentSong());
}

void ListeningHistory::onCurrentSongChanged(Song* song)
{
    auto newEntry = ListeningHistoryEntry::fromData(song, player.serviceName());
    workDispatcher.delayInvoke(DELAY, [=]() mutable { addSong(song, newEntry); });
}

void ListeningHistory::initialize()
{
    dataProvider.initialize();
    entries = this->dataProvider.toList();
    clearOutdatedEntries();
}

const QList<ListeningHistoryEntry>& ListeningHistory::toList() const
{
    return entries;
}

int ListeningHistory::count() const
{
    return toList().count();
}

void ListeningHistory::clear()
{
    workDispatcher.invoke([=]() mutable {
        dataProvider.clear();
        updateRemovedEntries();
    });
}

void ListeningHistory::removeById(int entryId)
{
    workDispatcher.invoke([=]() mutable {
        dataProvider.remove("id", QString("%1").arg(entryId));
        updateRemovedEntries();
    });
}

void ListeningHistory::removeByService(const QString& serviceName)
{
    workDispatcher.invoke([=]() mutable {
        dataProvider.remove("serviceName", serviceName);
        updateRemovedEntries();
    });
}

void ListeningHistory::removeManyById(const QList<int>& ids)
{
    workDispatcher.invoke([=]() mutable {
        dataProvider.removeMany(ids);
        updateRemovedEntries();
    });
}

void ListeningHistory::addSong(const Song* song, ListeningHistoryEntry& newEntry)
{
    if (!isEnabledSetting.value().toBool())
        return;

    auto previousEntry = previousEntryPerPlayer[player.serviceName()];

    if (previousEntry.equals(newEntry) || !newEntry.isValid() || player.playbackStatus() != PlaybackStatus::Playing)
        return;

    newEntry.id = dataProvider.add(newEntry);
    entries.append(newEntry);
    emit entryAdded(newEntry);
    previousEntryPerPlayer[player.serviceName()] = newEntry;
    LOG_DEBUG(logger, "new entry: " + song->toString() + ", id=" + QString("%1").arg(newEntry.id));
}

void ListeningHistory::updateRemovedEntries()
{
    auto removedEntries = entries.toSet().subtract(dataProvider.toList().toSet()).toList();
    for (auto entry : removedEntries) {
        int index = entries.indexOf(entry);
        entries.removeAt(index);
        emit entryRemoved(entry.id);
    }
}

void ListeningHistory::onIsEnabledChanged()
{
    if (!isEnabledSetting.value().toBool())
        clear();
}

TimeLimits dateToTimeLimit(const QDateTime& dateTime)
{
    QDate date = dateTime.date();
    QDate today = QDateTime::currentDateTime().date();
    QDate yesterday = today.addDays(-1);
    QDate lastWeek = today.addDays(-7);
    QDate lastMonth = today.addMonths(-1);
    QDate lastYear = today.addYears(-1);

    if (date == today)
        return TimeLimits::Today;
    else if (date == yesterday)
        return TimeLimits::Yesterday;
    else if (date >= lastWeek)
        return TimeLimits::LastWeek;
    else if (date >= lastMonth)
        return TimeLimits::LastMonth;
    else if (date >= lastYear)
        return TimeLimits::LastYear;
    else
        return TimeLimits::Never;
}

void ListeningHistory::clearOutdatedEntries()
{
    TimeLimits limit = static_cast<TimeLimits>(limitSetting.value().toInt());

    if (limit == TimeLimits::Never)
        return;

    workDispatcher.invoke([=]() mutable {
        LOG_DEBUG(logger, "Cleaning history ");
        QList<int> items;
        for (auto entry : entries) {
            TimeLimits entryLimit = dateToTimeLimit(entry.dateTime());
            if (entryLimit > limit) {
                items.append(entry.id);
                LOG_DEBUG(logger, "Removing entry " << entry.songTitle);
            }
        }
        dataProvider.removeMany(items);
        updateRemovedEntries();
    });
}
