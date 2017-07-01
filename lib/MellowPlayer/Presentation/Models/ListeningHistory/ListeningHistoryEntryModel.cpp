#include "ListeningHistoryEntryModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

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
    return dateTimeConverter.dateToString(entry.dateTime());
}

QString ListeningHistoryEntryModel::getTime() const {
    return dateTimeConverter.timeToString(entry.dateTime());
}

QString ListeningHistoryEntryModel::getDateCategory() const {
    return dateTimeConverter.dateToCategory(entry.dateTime());
}
