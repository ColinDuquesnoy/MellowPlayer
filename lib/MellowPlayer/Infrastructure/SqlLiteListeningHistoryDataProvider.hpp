#pragma once

#include <MellowPlayer/UseCases/Interfaces/IListeningHistoryDataProvider.hpp>
#include <QtSql/QSqlDatabase>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_STRUCT(Entities, ListeningHistoryEntry)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SqlLiteListeningHistoryDataProvider: public UseCases::IListeningHistoryDataProvider {
public:
    SqlLiteListeningHistoryDataProvider();
    ~SqlLiteListeningHistoryDataProvider();

    void initialize() override;
    int add(const Entities::ListeningHistoryEntry& entry) override;
    void clear() override;
    void remove(const QString& filterKey, const QString& filterValue) override;
    void removeMany(const QList<int>& identifiers) override;
    QList<Entities::ListeningHistoryEntry> getAll() const override;

    static QString getDatabasePath();

private:
    bool openDatabase();
    void initDatabase();

    UseCases::ILogger& logger;
    QSqlDatabase database;
};

END_MELLOWPLAYER_NAMESPACE
