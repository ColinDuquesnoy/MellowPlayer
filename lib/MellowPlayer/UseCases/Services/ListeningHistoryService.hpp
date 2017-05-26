#pragma once

#include <QMap>
#include <QMutex>
#include <QList>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities/ListeningHistoryEntry.hpp>
#include <MellowPlayer/UseCases/IWorkDispatcher.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, Song)
PREDECLARE_MELLOWPLAYER_CLASS(Entities, Song)

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IListeningHistoryDataProvider;
class ILogger;
class IPlayer;
class Setting;
class Settings;

class ListeningHistoryService: public QObject {
    Q_OBJECT
public:
    ListeningHistoryService(IListeningHistoryDataProvider& model, IPlayer& player, IWorkDispatcher& workDispatcher,
                            Settings& settings);

    void initialize();
    const QList<Entities::ListeningHistoryEntry>& getEntries() const;
    int count() const ;
    void clear();
    void removeById(int entryId);
    void removeByService(const QString& serviceName);
    void removeManyById(const QList<int> &ids);

signals:
    void entryAdded(const Entities::ListeningHistoryEntry& entry);
    void entryRemoved(int entryId);
    void entriesCleared();

private slots:
    void onPlaybackStatusChanged();
    void onCurrentSongChanged(Entities::Song* song);
    void onIsEnabledChanged();

private:
    void addSong(const Entities::Song* song, Entities::ListeningHistoryEntry& newEntry);
    void updateRemovedEntries();

    ILogger& logger;
    IListeningHistoryDataProvider& dataProvider;
    IPlayer& player;
    IWorkDispatcher& workDispatcher;
    QMap<QString, Entities::ListeningHistoryEntry> previousEntryPerPlayer;
    QList<Entities::ListeningHistoryEntry> entries;
    Setting& isEnabledSetting;
};

END_MELLOWPLAYER_NAMESPACE
