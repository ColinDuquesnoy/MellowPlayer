#pragma once

#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeNetworkProxies: public INetworkProxies
    {
    public:
        std::shared_ptr<NetworkProxy> get(const QString&) const override
        {
            return std::make_shared<NetworkProxy>();
        }
    };

}