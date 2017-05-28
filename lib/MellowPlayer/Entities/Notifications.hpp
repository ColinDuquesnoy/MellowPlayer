#pragma once

#include <QString>
#include <QDateTime>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

enum class NotificationType {
    NewSong,
    Resumed,
    Paused,
    NewVersionAvailable
};

struct Notification {
    QString title;
    QString description;
    QString icon;
    NotificationType type;

    QString toString() const { return title + " - " + description; }

    inline bool operator==(const Notification& other) const {
        return title == other.title && description == other.description;
    }

    inline bool operator!=(const Notification& other) const {
        return !this->operator==(other);
    }
};

END_MELLOWPLAYER_NAMESPACE
