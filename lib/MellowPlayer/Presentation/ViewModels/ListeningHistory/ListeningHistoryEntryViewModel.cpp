#include "ListeningHistoryEntryViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

ListeningHistoryEntryViewModel::ListeningHistoryEntryViewModel(const ListeningHistoryEntry& entry, QObject* parent):
        QObject(parent), entry(entry) {

}

QString ListeningHistoryEntryViewModel::getSongId() const {
    return entry.songUniqueId;
}

QString ListeningHistoryEntryViewModel::getTitle() const {
    return entry.songTitle;
}

QString ListeningHistoryEntryViewModel::getArtist() const {
    return entry.artist;
}

QString ListeningHistoryEntryViewModel::getArtUrl() const {
    return entry.artUrl;
}

QString ListeningHistoryEntryViewModel::getService() const {
    return entry.serviceName;
}

QString ListeningHistoryEntryViewModel::getDate() const {
    return dateTimeConverter.dateToString(entry.dateTime());
}

QString ListeningHistoryEntryViewModel::getTime() const {
    return dateTimeConverter.timeToString(entry.dateTime());
}

QString ListeningHistoryEntryViewModel::getDateCategory() const {
    return dateTimeConverter.dateToCategory(entry.dateTime());
}
