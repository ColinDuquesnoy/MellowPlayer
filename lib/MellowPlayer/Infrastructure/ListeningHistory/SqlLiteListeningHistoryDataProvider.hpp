#pragma once

#include <MellowPlayer/Application/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <QtSql/QSqlDatabase>

namespace MellowPlayer::Application {

    class ILogger;
    struct ListeningHistoryEntry;

}

namespace MellowPlayer::Infrastructure {

    class SqlLiteListeningHistoryDataProvider: public Application::IListeningHistoryDataProvider {
    public:
        SqlLiteListeningHistoryDataProvider();
        ~SqlLiteListeningHistoryDataProvider();

        void initialize() override;
        int add(const Application::ListeningHistoryEntry& entry) override;
        void clear() override;
        void remove(const QString& filterKey, const QString& filterValue) override;
        void removeMany(const QList<int>& identifiers) override;
        QList<Application::ListeningHistoryEntry> getAll() const override;

        static QString getDatabasePath();

    private:
        bool openDatabase();
        void initDatabase();

        Application::ILogger& logger;
        QSqlDatabase database;
    };

}
