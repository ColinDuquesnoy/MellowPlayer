#pragma once

#include <QMap>
#include <QMutex>
#include <QList>
#include <MellowPlayer/Application/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Application/IWorkDispatcher.hpp>

namespace MellowPlayer::Application {

    class Song;
    class IListeningHistoryDataProvider;
    class ILogger;
    class IPlayer;
    class Setting;
    class Settings;

    class ListeningHistory: public QObject {
        Q_OBJECT
    public:
        ListeningHistory(IListeningHistoryDataProvider& model, IPlayer& player, IWorkDispatcher& workDispatcher,
                                Settings& settings);

        void initialize();
        const QList<Application::ListeningHistoryEntry>& getEntries() const;
        int count() const ;
        void clear();
        void removeById(int entryId);
        void removeByService(const QString& serviceName);
        void removeManyById(const QList<int> &ids);

    signals:
        void entryAdded(const Application::ListeningHistoryEntry& entry);
        void entryRemoved(int entryId);
        void entriesCleared();

    private slots:
        void onPlaybackStatusChanged();
        void onCurrentSongChanged(Application::Song* song);
        void onIsEnabledChanged();
        void clearOutdatedEntries();

    private:
        void addSong(const Application::Song* song, Application::ListeningHistoryEntry& newEntry);
        void updateRemovedEntries();

        ILogger& logger;
        IListeningHistoryDataProvider& dataProvider;
        IPlayer& player;
        IWorkDispatcher& workDispatcher;
        QMap<QString, Application::ListeningHistoryEntry> previousEntryPerPlayer;
        QList<Application::ListeningHistoryEntry> entries;
        Setting& isEnabledSetting;
        Setting& limitSetting;
    };

}
