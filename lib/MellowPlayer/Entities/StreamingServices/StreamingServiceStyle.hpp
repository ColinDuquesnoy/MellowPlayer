#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

struct StreamingServiceStyle {
    QString accent;
    QString background;
    QString foreground;
    QString primary;
    QString primaryForeground;
    QString secondary;
    QString secondaryForeground;

    bool isEmpty() const {
        return accent.isEmpty() || background.isEmpty() || foreground.isEmpty() || primary.isEmpty() ||
               primaryForeground.isEmpty() || secondary.isEmpty() || secondaryForeground.isEmpty();
    }
};

END_MELLOWPLAYER_NAMESPACE
