#pragma once

#include <QMap>
#include <QMutex>
#include "IListeningHistoryDataProvider.hpp"
#include "../Logging/ILogger.hpp"
#include "../Player/IPlayer.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ListeningHistory: public QObject {
    Q_OBJECT
public:
    ListeningHistory(IListeningHistoryDataProvider& model, IPlayer& player);

    const QList<ListeningHistoryEntry>& getEntries() const;
    void clear();
    void removeById(int entryId);
    void removeByService(const QString& serviceName);

signals:
    void entryAdded(const ListeningHistoryEntry& entry);
    void entryRemoved(int i);
    void entriesCleared();

private slots:
    void onPlaybackStatusChanged();
    void onCurrentSongChanged(Song* song);

private:
    ILogger& logger;
    IListeningHistoryDataProvider& model;
    IPlayer& player;
    QMap<QString, ListeningHistoryEntry> previousEntryPerPlayer;
    QList<ListeningHistoryEntry> entries;
    QMutex mutex;
};

END_MELLOWPLAYER_NAMESPACE
