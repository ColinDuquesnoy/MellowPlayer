#pragma once

#include <QDebug>
#include <QVariant>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <MellowPlayer/Application/Player/IPlayer.hpp>

inline QVariantMap getSongVariantMap(QString title, QString uniqueId, bool playing=true, QString artist="artistName") {
    QVariantMap map;
    map["position"] = 1.0;
    map["playbackStatus"] = static_cast<int>(playing ?
                                             MellowPlayer::Application::PlaybackStatus::Playing :
                                             MellowPlayer::Application::PlaybackStatus::Paused);
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

inline QString readFile(const QString& path) {
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

inline bool writeFile(const QString& path, const QString& content) {
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    qDebug() << "Writing file: " << path;

    QTextStream stream(&file);
    stream << content;
    return true;
}