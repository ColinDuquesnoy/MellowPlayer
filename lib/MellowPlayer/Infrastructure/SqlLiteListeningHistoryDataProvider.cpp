#include <QtCore/QVariant>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <MellowPlayer/Entities/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "System/FileHelper.hpp"
#include "SqlLiteListeningHistoryDataProvider.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

SqlLiteListeningHistoryDataProvider::SqlLiteListeningHistoryDataProvider() :
        logger(LoggingManager::instance().getLogger("SqlLiteListeningHistoryDataProvider")) {

}

SqlLiteListeningHistoryDataProvider::~SqlLiteListeningHistoryDataProvider() {
    database.close();
}

bool SqlLiteListeningHistoryDataProvider::openDatabase() {
    std::stringstream stream;
    auto path = getDatabasePath();
    LOG_DEBUG(logger, "opening listening history db: " + path)
    database.setDatabaseName(path);
    if (!database.open()) {
        LOG_WARN(logger, "connection with database failed: " + path)
        return false;
    }
    LOG_INFO(logger, "connected to database: " + path)
    return true;
}

int SqlLiteListeningHistoryDataProvider::add(const ListeningHistoryEntry& entry) {
    QSqlQuery query;
    query.prepare("INSERT INTO song (songUniqueId, songTitle, artist, album, artUrl, serviceName, time) VALUES (:songUniqueId, :songTitle, :artist, :album, :artUrl, :serviceName, :time)");
    query.bindValue(":songUniqueId", entry.songUniqueId);
    query.bindValue(":songTitle", entry.songTitle);
    query.bindValue(":artist", entry.artist);
    query.bindValue(":album", entry.album);
    query.bindValue(":artUrl", entry.artUrl);
    query.bindValue(":serviceName", entry.serviceName);
    query.bindValue(":time", entry.time);

    if (!query.exec())
        LOG_WARN(logger, "failed to add listening history entry to db: " + query.lastError().text());

    return query.lastInsertId().toInt();
}

void SqlLiteListeningHistoryDataProvider::clear() {
    QSqlQuery query;
    query.prepare("DELETE FROM song");

    if (!query.exec())
        LOG_WARN(logger, "failed to clear listening history: " + query.lastError().text());
}

void SqlLiteListeningHistoryDataProvider::remove(const QString& filterKey, const QString& filterValue) {
    QSqlQuery query;
    query.prepare(QString("DELETE FROM song WHERE %1=(:%1)").arg(filterKey));
    query.bindValue(QString(":%1").arg(filterKey), filterValue);

    if (!query.exec())
        LOG_WARN(logger, "failed to clear listening history: " + query.lastError().text());
}

void SqlLiteListeningHistoryDataProvider::removeMany(const QList<int>& identifiers) {
    QStringList idStrings;
    foreach(int id, identifiers)
        idStrings << QString::number(id);
    QString numberList = idStrings.join(",");

    QSqlQuery query;
    QString queryString = QString("DELETE FROM song WHERE id IN (%1)").arg(numberList);

    if (!query.exec(queryString))
        LOG_WARN(logger, "failed to clear listening history: " + query.lastError().text());
}

QList<ListeningHistoryEntry> SqlLiteListeningHistoryDataProvider::getAll() const {
    QList<ListeningHistoryEntry> retVal;

    QSqlQuery query("SELECT * FROM song ORDER BY time");
    int idId = query.record().indexOf("id");
    int idUniqueId = query.record().indexOf("songUniqueId");
    int idTitle = query.record().indexOf("songTitle");
    int idArtist = query.record().indexOf("artist");
    int idAlbum = query.record().indexOf("album");
    int idArtUrl = query.record().indexOf("artUrl");
    int idServiceName = query.record().indexOf("serviceName");
    int idTime = query.record().indexOf("time");

    while (query.next())
    {
        ListeningHistoryEntry entry;
        entry.songUniqueId = query.value(idUniqueId).toString();
        entry.songTitle = query.value(idTitle).toString();
        entry.artist = query.value(idArtist).toString();
        entry.album = query.value(idAlbum).toString();
        entry.artUrl = query.value(idArtUrl).toString();
        entry.serviceName = query.value(idServiceName).toString();
        entry.time = query.value(idTime).toString();
        entry.id = query.value(idId).toInt();
        retVal.append(entry);
    }

    return retVal;
}

void SqlLiteListeningHistoryDataProvider::initDatabase() {
    if (database.tables().count() == 0) {
        LOG_DEBUG(logger, "creating database");
        QSqlQuery query;
        query.prepare("CREATE TABLE song(id INTEGER PRIMARY KEY, songUniqueId TEXT, songTitle TEXT, artist TEXT, album TEXT, "
                      "artUrl TEXT, serviceName TEXT, time TEXT);");
        if (!query.exec())
            LOG_WARN(logger, "failed to create song table: " + query.lastError().text());
    }
}

void SqlLiteListeningHistoryDataProvider::initialize() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    if (openDatabase())
        initDatabase();
}

QString SqlLiteListeningHistoryDataProvider::getDatabasePath() {
    return FileHelper::appDataDirectory() + "history.db";
}
