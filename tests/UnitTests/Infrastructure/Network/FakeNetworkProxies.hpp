#pragma once

#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeNetworkProxies: public INetworkProxies
    {
    public:
        std::shared_ptr<NetworkProxy> get(const QString& name) const override
        {
            if (items.contains(name))
                return items[name];
            return std::make_shared<NetworkProxy>();
        }

        QMap<QString, std::shared_ptr<NetworkProxy>> items;
    };

}