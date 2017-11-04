#pragma once

#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <QList>
#include <QMap>
#include <QMutex>

namespace MellowPlayer::Domain
{
    class Song;
    class IListeningHistoryDataProvider;
    class ILogger;
    class IPlayer;
    class Setting;
    class Settings;
    class IWorkDispatcher;

    class ListeningHistory : public QObject
    {
        Q_OBJECT
    public:
        ListeningHistory(IListeningHistoryDataProvider& model, IPlayer& player, IWorkDispatcher& workDispatcher, Settings& settings);

        void initialize();
        const QList<Domain::ListeningHistoryEntry>& toList() const;
        int count() const;
        void clear();
        void removeById(int entryId);
        void removeByService(const QString& serviceName);
        void removeManyById(const QList<int>& ids);

    signals:
        void entryAdded(const Domain::ListeningHistoryEntry& entry);
        void entryRemoved(int entryId);
        void entriesCleared();

    private slots:
        void onPlaybackStatusChanged();
        void onCurrentSongChanged(Domain::Song* song);
        void onIsEnabledChanged();
        void clearOutdatedEntries();

    private:
        void addSong(const Domain::Song* song, Domain::ListeningHistoryEntry& newEntry);
        void updateRemovedEntries();

        ILogger& logger;
        IListeningHistoryDataProvider& dataProvider;
        IPlayer& player;
        IWorkDispatcher& workDispatcher;
        QMap<QString, Domain::ListeningHistoryEntry> previousEntryPerPlayer;
        QList<Domain::ListeningHistoryEntry> entries;
        Setting& isEnabledSetting;
        Setting& limitSetting;
    };
}
