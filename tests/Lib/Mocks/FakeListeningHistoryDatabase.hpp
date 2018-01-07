#pragma once

#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDatabase.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>

class FakeListeningHistoryDatabase : public MellowPlayer::Domain::IListeningHistoryDatabase
{
public:
    bool initialized = false;

    bool initialize()
    {
        initialized = true;
        return initialized;
    };

    int add(const MellowPlayer::Domain::ListeningHistoryEntry& entry)
    {
        auto newEntry(entry);
        newEntry.id = entries.count() + 1;
        entries.append(newEntry);
        return entries.count();
    };

    void clear()
    {
        entries.clear();
    };

    void remove(const QString& filterKey, const QString& filterValue)
    {
        QList<MellowPlayer::Domain::ListeningHistoryEntry> toRemove;
        for (int i = 0; i < entries.count(); ++i) {
            auto& entry = entries.at(i);
            if ((filterKey == "id" && entry.id == filterValue.toInt()) || (filterKey == "serviceName" && entry.serviceName == filterValue))
                toRemove.append(entry);
        }
        for (auto& entry : toRemove)
            entries.removeOne(entry);
    };

    void removeMany(const QList<int>& items)
    {
        for (int id : items) {
            remove("id", QString::number(id));
        }
    }

    QList<MellowPlayer::Domain::ListeningHistoryEntry> toList() const
    {
        return entries;
    };

private:
    QList<MellowPlayer::Domain::ListeningHistoryEntry> entries;
};