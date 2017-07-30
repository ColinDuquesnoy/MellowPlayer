#pragma once

#include <MellowPlayer/Application/Player/Song.hpp>
#include <QDateTime>

namespace MellowPlayer::Application
{
    struct ListeningHistoryEntry
    {
        int id;
        QString songUniqueId;
        QString songTitle;
        QString artist;
        QString album;
        QString artUrl;
        QString serviceName;
        QString time;

        QDateTime dateTime() const
        {
            return QDateTime::fromString(time, Qt::ISODate);
        }

        bool isValid() const
        {
            return !songUniqueId.isEmpty() && !songTitle.isEmpty() && !serviceName.isEmpty();
        }

        bool equals(const ListeningHistoryEntry& other) const
        {
            return other.serviceName == serviceName && other.songUniqueId == songUniqueId && other.songTitle == songTitle && other.artist == artist
            && other.album == album && other.artUrl == artUrl;
        }

        bool operator==(const ListeningHistoryEntry& other) const
        {
            return other.id == id;
        }

        bool operator!=(const ListeningHistoryEntry& other) const
        {
            return !operator==(other);
        }

        static ListeningHistoryEntry fromData(const Song* song, const QString& serviceName)
        {
            ListeningHistoryEntry entry;
            entry.id = 0;
            QDateTime now = QDateTime::currentDateTime();

            if (song != nullptr && song->isValid()) {
                entry.songUniqueId = song->uniqueId();
                entry.songTitle = song->title();
                entry.artist = song->artist();
                entry.album = song->album();
                entry.artUrl = song->artUrl();
                entry.serviceName = serviceName;
                entry.time = now.toString(Qt::ISODate);
            }

            return entry;
        }

        operator int() const
        {
            return id;
        }
    };
}
