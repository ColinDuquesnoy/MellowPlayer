#pragma once

#include <MellowPlayer/Application/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <QtSql/QSqlDatabase>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_STRUCT(Application, ListeningHistoryEntry)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

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

END_MELLOWPLAYER_NAMESPACE
