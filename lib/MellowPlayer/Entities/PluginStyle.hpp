#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

struct PluginStyle
{
    QString theme;
    QString accent;
    QString background;
    QString foreground;
    QString primary;
    QString primaryForeground;
    QString secondary;
    QString secondaryForeground;

    static PluginStyle defaultStyle();
};

END_MELLOWPLAYER_NAMESPACE
