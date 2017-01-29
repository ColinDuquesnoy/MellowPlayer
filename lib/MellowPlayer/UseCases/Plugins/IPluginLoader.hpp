#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IPluginLoader: public NonCopyable {
public:
    virtual ~IPluginLoader() = default;

    virtual Entities::PluginList loadPlugins() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
