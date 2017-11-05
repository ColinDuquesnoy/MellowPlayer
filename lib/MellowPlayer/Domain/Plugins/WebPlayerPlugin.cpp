#include "WebPlayerPlugin.hpp"
#include "IPluginVisitor.hpp"

using namespace MellowPlayer::Domain;

void WebPlayerPlugin::accept(IPluginVisitor& visitor)
{
    visitor.visit(*this);
}
