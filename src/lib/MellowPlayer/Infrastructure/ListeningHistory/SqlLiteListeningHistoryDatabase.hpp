#pragma once

#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDatabase.hpp>
#include <QtSql/QSqlDatabase>

namespace MellowPlayer::Domain
{
    class ILogger;
    struct ListeningHistoryEntry;
}

namespace MellowPlayer::Infrastructure
{
    class SqlLiteListeningHistoryDatabase : public Domain::IListeningHistoryDatabase
    {
    public:
        SqlLiteListeningHistoryDatabase();
        ~SqlLiteListeningHistoryDatabase();

        bool initialize() override;
        int add(const Domain::ListeningHistoryEntry& entry) override;
        void clear() override;
        void remove(const QString& filterKey, const QString& filterValue) override;
        void removeMany(const QList<int>& identifiers) override;
        QList<Domain::ListeningHistoryEntry> toList() const override;

        static QString getDatabasePath();

    private:
        bool openDatabase();
        bool initDatabase();

        Domain::ILogger& logger_;
        QSqlDatabase database_;
    };
}
