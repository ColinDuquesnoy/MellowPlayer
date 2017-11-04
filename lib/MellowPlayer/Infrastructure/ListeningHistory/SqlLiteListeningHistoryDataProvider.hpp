#pragma once

#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <QtSql/QSqlDatabase>

namespace MellowPlayer::Domain
{
    class ILogger;
    struct ListeningHistoryEntry;
}

namespace MellowPlayer::Infrastructure
{
    class SqlLiteListeningHistoryDataProvider : public Domain::IListeningHistoryDataProvider
    {
    public:
        SqlLiteListeningHistoryDataProvider();
        ~SqlLiteListeningHistoryDataProvider();

        void initialize() override;
        int add(const Domain::ListeningHistoryEntry& entry) override;
        void clear() override;
        void remove(const QString& filterKey, const QString& filterValue) override;
        void removeMany(const QList<int>& identifiers) override;
        QList<Domain::ListeningHistoryEntry> toList() const override;

        static QString getDatabasePath();

    private:
        bool openDatabase();
        void initDatabase();

        Domain::ILogger& logger_;
        QSqlDatabase database_;
    };
}
