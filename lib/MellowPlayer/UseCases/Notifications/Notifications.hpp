#pragma once

#include <QString>
#include <QDateTime>
#include <QIcon>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

enum class NotificationType {
    Song,
    Paused,
    Stopped,
    NewVersionAvailable
};

struct Notification {
    QString title;
    QString description;
    QString icon;
    NotificationType type;

    QString toString() const { return title + " - " + description; }
};

END_MELLOWPLAYER_NAMESPACE
