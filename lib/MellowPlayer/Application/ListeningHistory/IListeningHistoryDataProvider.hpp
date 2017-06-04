#pragma once

#include <QList>
#include <QString>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_STRUCT(Application, ListeningHistoryEntry)

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class IListeningHistoryDataProvider {
public:
    virtual ~IListeningHistoryDataProvider() = default;
    virtual void initialize() = 0;
    virtual int add(const Application::ListeningHistoryEntry& entry) = 0;
    virtual void clear() = 0;
    virtual void remove(const QString& filterKey, const QString& filterValue) = 0;
    virtual void removeMany(const QList<int>& items) = 0;

    virtual QList<Application::ListeningHistoryEntry> getAll() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
