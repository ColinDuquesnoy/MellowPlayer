#include <QDateTime>
#include <QSet>
#include <QVariant>
#include <QTimer>
#include <algorithm>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDatabase.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/ListeningHistory/TimeLimits.hpp>
#include <MellowPlayer/Domain/IWorkDispatcher.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>

using namespace MellowPlayer::Domain;

ListeningHistory::ListeningHistory(IListeningHistoryDatabase& model, IPlayer& player, Settings& settings)
        : isEnabledSetting_(settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY)),
          limitSetting_(settings.get(SettingKey::PRIVACY_LISTENING_HISTORY_LIMIT)),
          logger_(Loggers::logger("ListeningHistory")),
          database_(model),
          player_(player)
{
    connect(&player, &IPlayer::currentSongChanged, this, &ListeningHistory::onSongChanged);
    connect(&player, &IPlayer::playbackStatusChanged, this, &ListeningHistory::onPlaybackStatusChanged);
    connect(&isEnabledSetting_, &Setting::valueChanged, this, &ListeningHistory::onIsEnabledChanged);
    connect(&limitSetting_, &Setting::valueChanged, this, &ListeningHistory::clearOutdatedEntries);
}

void ListeningHistory::onPlaybackStatusChanged()
{
    addSong(player_.currentSong());
}

void ListeningHistory::onSongChanged(Song *song)
{
    addSong(song);
}

void ListeningHistory::addSong(Song* song)
{
    auto newEntry = ListeningHistoryEntry::fromData(song, player_.serviceName());
    addSong(song, newEntry);
}

void ListeningHistory::initialize()
{
    database_.initialize();
    entries_ = database_.toList();
    clearOutdatedEntries();
}

QList<ListeningHistoryEntry> ListeningHistory::toList() const
{
    return entries_;
}

int ListeningHistory::count() const
{
    return toList().count();
}

void ListeningHistory::clear()
{
    database_.clear();
    updateRemovedEntries();
}

void ListeningHistory::removeById(int entryId)
{
    database_.remove("id", QString("%1").arg(entryId));
    updateRemovedEntries();
}

void ListeningHistory::removeByService(const QString& serviceName)
{
    database_.remove("serviceName", serviceName);
    updateRemovedEntries();
}

void ListeningHistory::removeManyById(const QList<int>& ids)
{
    database_.removeMany(ids);
    updateRemovedEntries();
}

void ListeningHistory::addSong(const Song* song, ListeningHistoryEntry& newEntry)
{
    if (!isEnabledSetting_.value().toBool())
        return;

    auto previousEntry = previousEntryPerPlayer_[player_.serviceName()];

    if (previousEntry.equals(newEntry) || !newEntry.isValid() || player_.playbackStatus() != PlaybackStatus::Playing)
        return;

    newEntry.id = database_.add(newEntry);
    entries_.append(newEntry);
    emit entryAdded(newEntry);
    previousEntryPerPlayer_[player_.serviceName()] = newEntry;
    LOG_DEBUG(logger_, "new entry: " + song->toString() + ", id=" + QString("%1").arg(newEntry.id));
}

void ListeningHistory::updateRemovedEntries()
{
    auto removedEntries = entries_.toSet().subtract(database_.toList().toSet()).toList();
    for (auto entry : removedEntries) {
        int index = entries_.indexOf(entry);
        entries_.removeAt(index);
        emit entryRemoved(entry.id);
    }
}

void ListeningHistory::onIsEnabledChanged()
{
    if (!isEnabledSetting_.value().toBool())
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
    TimeLimits limit = static_cast<TimeLimits>(limitSetting_.value().toInt());

    if (limit == TimeLimits::Never)
        return;

    LOG_INFO(logger_, "Cleaning history ");
    QList<int> items;
    for (auto entry : entries_) {
        TimeLimits entryLimit = dateToTimeLimit(entry.dateTime());
        if (entryLimit > limit) {
            items.append(entry.id);
            LOG_DEBUG(logger_, "Removing entry " << entry.songTitle);
        }
    }
    database_.removeMany(items);
    updateRemovedEntries();
}
