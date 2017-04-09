#pragma once

#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_STRUCT(Entities, ListeningHistoryEntry)

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IListeningHistoryDataProvider {
public:
    virtual void initialize() = 0;
    virtual int add(const Entities::ListeningHistoryEntry& entry) = 0;
    virtual void clear() = 0;
    virtual void remove(const QString& filterKey, const QString& filterValue) = 0;

    virtual QList<Entities::ListeningHistoryEntry> getAll() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
