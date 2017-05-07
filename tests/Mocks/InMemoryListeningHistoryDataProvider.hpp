#include <MellowPlayer/UseCases/Interfaces/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Entities/ListeningHistoryEntry.hpp>


class InMemoryListeningHistoryDataProvider: public MellowPlayer::UseCases::IListeningHistoryDataProvider {
public:
    bool initialized = false;

    void initialize() {
        initialized = true;
    };

    int add(const MellowPlayer::Entities::ListeningHistoryEntry& entry) {
        auto newEntry(entry);
        newEntry.id = entries.count() + 1;
        entries.append(newEntry);
        return entries.count();
    };

    void clear() {
        entries.clear();
    };

    void remove(const QString& filterKey, const QString& filterValue) {
        QList<MellowPlayer::Entities::ListeningHistoryEntry> toRemove;
        for (int i = 0; i < entries.count(); ++i) {
            auto& entry = entries.at(i);
            if ((filterKey == "id" && entry.id == filterValue.toInt()) ||
                    (filterKey == "serviceName" && entry.serviceName == filterValue))
                toRemove.append(entry);
        }
        for(auto& entry: toRemove)
            entries.removeOne(entry);
    };

    QList<MellowPlayer::Entities::ListeningHistoryEntry> getAll() const {
        return entries;
    };

private:
    QList<MellowPlayer::Entities::ListeningHistoryEntry> entries;
};