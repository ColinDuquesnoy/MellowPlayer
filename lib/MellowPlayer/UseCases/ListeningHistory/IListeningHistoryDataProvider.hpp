#pragma once

#include "ListeningHistoryEntry.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IListeningHistoryDataProvider {
public:
    virtual int add(const ListeningHistoryEntry& entry) = 0;
    virtual void clear() = 0;
    virtual void remove(const QString& filterKey, const QString& filterValue) = 0;

    virtual QList<ListeningHistoryEntry> getAll() const = 0;
};

END_MELLOWPLAYER_NAMESPACE