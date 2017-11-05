#pragma once

namespace MellowPlayer::Domain
{
    class WebPlayerPlugin;

    class IPluginVisitor
    {
    public:
        virtual ~IPluginVisitor() = default;

        virtual void visit(WebPlayerPlugin& playerPlugin) = 0;
    };
}
