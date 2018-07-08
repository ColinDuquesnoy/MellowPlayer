#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceLoader.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceWatcher.hpp>
#include <UnitTests/Infrastructure/Application/FakeQtApplication.hpp>
#include <catch/catch.hpp>
#include <QtTest/QSignalSpy>
#include <UnitTests/Domain/Settings/FakeSettingsStore.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("NetworkProxy are added when new streaming services are added")
{
    GIVEN("An empty list of streaming services")
    {
        FakeStreamingServiceLoader streamingServiceLoader;
        FakeStreamingServiceWatcher streamingServiceWatcher;
        FakeSettingsStore settingsStore;
        StreamingServices streamingServices(streamingServiceLoader, streamingServiceWatcher);
        NetworkProxies networkProxies(settingsStore, streamingServices);

        WHEN("I load StreamingServices")
        {
            streamingServices.load();

            THEN("there is a NetworkProxy for Deezer")
            {
                REQUIRE(networkProxies.get("Deezer") != nullptr);
            }

            THEN("there is a NetworkProxy for Spotify")
            {
                REQUIRE(networkProxies.get("Spotify") != nullptr);
            }

            THEN("there is a NetworkProxy for Mixcloud")
            {
                REQUIRE(networkProxies.get("Mixcloud") != nullptr);
            }

            THEN("there is a NetworkProxy for Soundcloud")
            {
                REQUIRE(networkProxies.get("Soundcloud") != nullptr);
            }

            AND_WHEN("I enable a network proxy")
            {
                networkProxies.get("Deezer")->setEnabled(true);

                THEN("enabled state is saved in settings")
                {
                    REQUIRE(settingsStore.value("Deezer/networkProxy").toMap()["enabled"].toBool());
                }

                AND_WHEN("I set a network proxy host name")
                {
                    QString hostName = "Foo";
                    networkProxies.get("Deezer")->setHostName(hostName);

                    THEN("host name is saved in settings")
                    {
                        REQUIRE(settingsStore.value("Deezer/networkProxy").toMap()["hostName"].toString() == hostName);
                    }

                    AND_WHEN("I set a network proxy port")
                    {
                        int port = 42;
                        networkProxies.get("Deezer")->setPort(port);

                        THEN("host name is saved in settings")
                        {
                            REQUIRE(settingsStore.value("Deezer/networkProxy").toMap()["port"].toInt() == port);
                        }
                    }
                }
            }
        }
    }
}
