#pragma once

#include <MellowPlayer/Application/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Application/ListeningHistory/ListeningHistoryEntry.hpp>


class InMemoryListeningHistoryDataProvider: public MellowPlayer::Application::IListeningHistoryDataProvider {
public:
    bool initialized = false;

    void initialize() {
        initialized = true;
    };

    int add(const MellowPlayer::Application::ListeningHistoryEntry& entry) {
        auto newEntry(entry);
        newEntry.id = entries.count() + 1;
        entries.append(newEntry);
        return entries.count();
    };

    void clear() {
        entries.clear();
    };

    void remove(const QString& filterKey, const QString& filterValue) {
        QList<MellowPlayer::Application::ListeningHistoryEntry> toRemove;
        for (int i = 0; i < entries.count(); ++i) {
            auto& entry = entries.at(i);
            if ((filterKey == "id" && entry.id == filterValue.toInt()) ||
                    (filterKey == "serviceName" && entry.serviceName == filterValue))
                toRemove.append(entry);
        }
        for(auto& entry: toRemove)
            entries.removeOne(entry);
    };

    void removeMany(const QList<int>& items) {
        for(int id: items) {
            remove("id", QString::number(id));
        }
    }

    QList<MellowPlayer::Application::ListeningHistoryEntry> getAll() const {
        return entries;
    };

private:
    QList<MellowPlayer::Application::ListeningHistoryEntry> entries;
};