#pragma once

#include "IPlayerPlugin.hpp"

namespace MellowPlayer::Domain
{
    class WebPlayerScript;

    class WebPlayerPlugin: public IPlayerPlugin
    {
        Q_OBJECT
        CONSTANT_OBJECT_PROPERTY(WebPlayerScript, script)
        WRITABLE_PROPERTY(QString, url, setUrl)
    public:
        void accept(IPluginVisitor& visitor) override;
    };
}
