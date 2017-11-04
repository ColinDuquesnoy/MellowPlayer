#pragma once

#include <QList>
#include <QString>

namespace MellowPlayer::Domain
{
    struct ListeningHistoryEntry;

    class IListeningHistoryDataProvider
    {
    public:
        virtual ~IListeningHistoryDataProvider() = default;
        virtual void initialize() = 0;
        virtual int add(const Domain::ListeningHistoryEntry& entry) = 0;
        virtual void clear() = 0;
        virtual void remove(const QString& filterKey, const QString& filterValue) = 0;
        virtual void removeMany(const QList<int>& items) = 0;

        virtual QList<Domain::ListeningHistoryEntry> toList() const = 0;
    };
}
