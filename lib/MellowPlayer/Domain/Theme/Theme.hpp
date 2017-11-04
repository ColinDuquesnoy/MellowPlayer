#pragma once

#include <QObject>

namespace MellowPlayer::Domain
{
    struct Theme
    {
        QString accent;
        QString background;
        QString foreground;
        QString primary;
        QString primaryForeground;
        QString secondary;
        QString secondaryForeground;

        bool isEmpty() const
        {
            return accent.isEmpty() || background.isEmpty() || foreground.isEmpty() || primary.isEmpty() || primaryForeground.isEmpty()
            || secondary.isEmpty() || secondaryForeground.isEmpty();
        }
    };
}
