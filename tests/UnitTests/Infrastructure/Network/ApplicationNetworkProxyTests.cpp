#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Infrastructure/Network/ApplicationNetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceWatcher.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceLoader.hpp>
#include <UnitTests/Infrastructure/Network/FakeNetworkProxies.hpp>
#include <catch/catch.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("ApplicationNetworkProxyTests")
{
    GIVEN("A fake network proxy configuration where only Spotify's network proxy is enabled")
    {
        FakeStreamingServiceLoader streamingServiceLoader;
        FakeStreamingServiceWatcher streamingServiceWatcher;
        StreamingServices streamingServices(streamingServiceLoader, streamingServiceWatcher);
        streamingServices.load();

        FakeNetworkProxies networkProxies;
        auto spotifyNetworkProxy = make_shared<NetworkProxy>();
        spotifyNetworkProxy->setEnabled(true);
        spotifyNetworkProxy->setHostName("192.168.0.42");
        spotifyNetworkProxy->setPort(42);
        networkProxies.items["Spotify"] = spotifyNetworkProxy;

        ApplicationNetworkProxy applicationNetworkProxy(streamingServices, networkProxies);

        WHEN("I change the current service to Spotify")
        {
            streamingServices.setCurrent(&streamingServices.get("Spotify"));

            THEN("the application proxy use Spotify's network proxy settings")
            {
                REQUIRE(QNetworkProxy::applicationProxy().hostName() == spotifyNetworkProxy->hostName());
                REQUIRE(QNetworkProxy::applicationProxy().port() == spotifyNetworkProxy->port());
            }

            AND_WHEN("I change Spotify's network proxy host name")
            {
                spotifyNetworkProxy->setHostName("10.129.0.42");

                THEN("the application proxy use updated host name")
                {
                    REQUIRE(QNetworkProxy::applicationProxy().hostName() == spotifyNetworkProxy->hostName());
                }
            }

            AND_WHEN("I change the current service to another service")
            {
                streamingServices.setCurrent(&streamingServices.get("Deezer"));

                THEN("the application proxy doesn't use spotify network proxy settings anymore")
                {
                    REQUIRE(QNetworkProxy::applicationProxy().hostName() != spotifyNetworkProxy->hostName());
                    REQUIRE(QNetworkProxy::applicationProxy().port() != spotifyNetworkProxy->port());
                }
            }
        }
    }
}