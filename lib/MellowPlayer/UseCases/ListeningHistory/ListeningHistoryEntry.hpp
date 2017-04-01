#pragma once

#include <QDateTime>
#include "../Player/Song.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

struct ListeningHistoryEntry {
    int id;
    QString songUniqueId;
    QString songTitle;
    QString artist;
    QString album;
    QString artUrl;
    QString serviceName;
    QString time;

    bool isValid() const {
        return !songUniqueId.isEmpty() && !songTitle.isEmpty() && !artist.isEmpty() && !artUrl.isEmpty() && !serviceName.isEmpty();
    }

    bool equals(const ListeningHistoryEntry& other) const {
        return other.serviceName == serviceName &&
               other.songUniqueId == songUniqueId &&
               other.songTitle == songTitle &&
               other.artist == artist &&
               other.album == album &&
               other.artUrl == artUrl;
    }

    bool operator==(const ListeningHistoryEntry& other) const {
        return other.id == id;
    }

    bool operator!=(const ListeningHistoryEntry& other) const {
        return !operator==(other);
    }

    static ListeningHistoryEntry fromData(const Song* song, const QString& serviceName) {
        ListeningHistoryEntry entry;
        entry.id = 0;
        QDateTime now = QDateTime::currentDateTime();

        if (song != nullptr && song->isValid()) {
            entry.songUniqueId = song->getUniqueId();
            entry.songTitle = song->getTitle();
            entry.artist = song->getArtist();
            entry.album = song->getAlbum();
            entry.artUrl = song->getArtUrl();
            entry.serviceName = serviceName;
            entry.time = now.toString(Qt::ISODate);
        }

        return entry;
    }

    operator int() const {
        return id;
    }
};

END_MELLOWPLAYER_NAMESPACE

//inline uint qHash(const MellowPlayer::UseCases::ListeningHistoryEntry& entry) {
//    return qHash(entry.id, 0xa03f);
//}