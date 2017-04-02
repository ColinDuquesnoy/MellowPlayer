#include "ListeningHistoryEntryModel.hpp"
#include <QDebug>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

ListeningHistoryEntryModel::ListeningHistoryEntryModel(const ListeningHistoryEntry& entry, QObject* parent):
        QObject(parent), entry(entry) {

}

QString ListeningHistoryEntryModel::getSongId() const {
    return entry.songUniqueId;
}

QString ListeningHistoryEntryModel::getTitle() const {
    return entry.songTitle;
}

QString ListeningHistoryEntryModel::getArtist() const {
    return entry.artist;
}

QString ListeningHistoryEntryModel::getArtUrl() const {
    return entry.artUrl;
}

QString ListeningHistoryEntryModel::getService() const {
    return entry.serviceName;
}

QString ListeningHistoryEntryModel::getDate() const {
    return entry.time.split("T")[0];
}

QString ListeningHistoryEntryModel::getTime() const {
    return QDateTime::fromString(entry.time, Qt::ISODate).toLocalTime().time().toString(Qt::SystemLocaleShortDate);
}
