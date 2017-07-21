#pragma once

#include <QDateTime>
#include <QString>

namespace MellowPlayer::Application
{
    enum class NotificationType
    {
        NewSong,
        Resumed,
        Paused,
        NewVersionAvailable,
    };

    struct Notification
    {
        QString title;
        QString description;
        QString icon;
        NotificationType type;

        QString toString() const
        {
            return title + " - " + description;
        }

        inline bool operator==(const Notification &other) const
        {
            return title == other.title && description == other.description;
        }

        inline bool operator!=(const Notification &other) const
        {
            return !this->operator==(other);
        }
    };
}
