#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class PluginLoader: public UseCases::IPluginLoader {
public:
    PluginLoader(UseCases::LoggingManager& loggingManager);
    Entities::PluginList loadPlugins() const override;

private:
    UseCases::ILogger& logger_;
};

END_MELLOWPLAYER_NAMESPACE
