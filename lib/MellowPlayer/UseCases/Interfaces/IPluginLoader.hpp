#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IPluginLoader: public QObject {
public:
    virtual ~IPluginLoader() = default;

    virtual Entities::PluginList load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
