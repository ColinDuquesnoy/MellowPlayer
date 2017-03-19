#include "PluginStyle.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)

PluginStyle PluginStyle::defaultStyle() {
    return PluginStyle {
            "light",
            "#FFC107",
            "#ffffff",
            "#505050",
            "#5f81d4",
            "#ffffff",
            "#5f81d4",
            "#ffffff"
    };
}

