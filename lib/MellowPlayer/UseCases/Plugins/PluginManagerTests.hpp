#pragma once
#include <MellowPlayer/Macros.hpp>
#include "IPluginLoader.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PluginManager: public NonCopyable {
public:
    PluginManager(IPluginLoader& pluginLoader);

    const Entities::Plugin& plugin(const QString& name) const;

private:
    IPluginLoader& pluginLoader_;
    Entities::PluginList plugins_;
};

END_MELLOWPLAYER_NAMESPACE
