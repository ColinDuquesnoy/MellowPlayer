#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities.hpp>
#include "../Plugin/Plugin.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IPluginLoader: public QObject {
public:
    virtual ~IPluginLoader() = default;

    virtual UseCases::PluginList load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
