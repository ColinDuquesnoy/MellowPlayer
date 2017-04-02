#pragma once

#include <MellowPlayer/UseCases/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <QtSql/QSqlDatabase>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ListeningHistoryEntry)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SqlLiteListeningHistoryDataProvider: public UseCases::IListeningHistoryDataProvider {
public:
    SqlLiteListeningHistoryDataProvider();
    ~SqlLiteListeningHistoryDataProvider();

    int add(const UseCases::ListeningHistoryEntry& entry) override;
    void clear() override;
    void remove(const QString& filterKey, const QString& filterValue) override;
    QList<UseCases::ListeningHistoryEntry> getAll() const override;

private:
    bool openDatabase();
    void initDatabase();

    UseCases::ILogger& logger;
    QSqlDatabase database;
};

END_MELLOWPLAYER_NAMESPACE
