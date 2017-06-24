#pragma once

#include <QVariant>

inline QVariantMap getSongVariantMap(QString title, QString uniqueId, bool playing=true, QString artist="artistName") {
    QVariantMap map;
    map["position"] = 1.0;
    map["playbackStatus"] = static_cast<int>(playing ? PlaybackStatus::Playing: PlaybackStatus::Paused);
    map["canSeek"] = true;
    map["canGoNext"] = true;
    map["canGoPrevious"] = true;
    map["canAddToFavorites"] = true;
    map["songId"] = uniqueId;
    map["songTitle"] = title;
    map["artistName"] = artist;
    map["albumTitle"] = "albumTitle";
    map["artUrl"] = "artUrl";
    map["isFavorite"] = true;
    map["volume"] = 0.5;
    map["duration"] = 350.0;
    return map;
}
