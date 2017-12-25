#include <MellowPlayer/Infrastructure/Network/NetworkProxy.h>
#include <catch.hpp>
#include <QtTest/QSignalSpy>

using namespace MellowPlayer::Infrastructure;

SCENARIO("NetworkProxyTests")
{
    GIVEN("An empty network proxy")
    {
        NetworkProxy networkProxy;

        QSignalSpy changedSpy(&networkProxy, &NetworkProxy::changed);
        QSignalSpy enabledChangedSpy(&networkProxy, &NetworkProxy::enabledChanged);
        QSignalSpy hostNameChangedSpy(&networkProxy, &NetworkProxy::hostNameChanged);
        QSignalSpy portChangedSpy(&networkProxy, &NetworkProxy::portChanged);

        REQUIRE(networkProxy.rawData().count() == 0);

        WHEN("I call isEnabled")
        {
            THEN("it returns false")
            {
                REQUIRE(!networkProxy.isEnabled());
            }

            AND_THEN("create return a QNetworkProxy with type set to DefaultProxy")
            {
                REQUIRE(networkProxy.create().type() == QNetworkProxy::DefaultProxy);
            }

            AND_WHEN("I set isEnabled to true")
            {
                networkProxy.setEnabled(true);

                THEN("isEnabled returns true")
                {
                    REQUIRE(networkProxy.isEnabled());
                }

                AND_THEN("enabledChanged signal is emitted")
                {
                    REQUIRE(enabledChangedSpy.count() == 1);
                }

                AND_THEN("changed signal is emitted")
                {
                    REQUIRE(changedSpy.count() == 1);
                }

                AND_THEN("create return a QNetworkProxy with type set to HttpProxy")
                {
                    REQUIRE(networkProxy.create().type() == QNetworkProxy::HttpProxy);
                }

                AND_THEN("rawData contains one entry")
                {
                    REQUIRE(networkProxy.rawData().count() == 1);
                }
            }
        }

        WHEN("I call hostName")
        {
            THEN("it returns an empty string")
            {
                REQUIRE(networkProxy.hostName().isEmpty());
            }

            AND_THEN("create return QNetworkProxy with empty host")
            {
                REQUIRE(networkProxy.create().hostName().isEmpty());
            }

            AND_WHEN("I set hostName to 192.168.0.1")
            {
                networkProxy.setHostName("192.168.0.1");

                THEN("hostName is set to 192.168.0.1")
                {
                    REQUIRE(networkProxy.hostName() == "192.168.0.1");
                }

                AND_THEN("hostNameChanged signal is emitted")
                {
                    REQUIRE(hostNameChangedSpy.count() == 1);
                }

                AND_THEN("changed signal is emitted")
                {
                    REQUIRE(changedSpy.count() == 1);
                }

                AND_THEN("create return QNetworkProxy with hostName set to 192.168.0.1")
                {
                    REQUIRE(networkProxy.create().hostName() == "192.168.0.1");
                }

                AND_THEN("rawData contains one entry")
                {
                    REQUIRE(networkProxy.rawData().count() == 1);
                }
            }
        }

        WHEN("I call port")
        {
            THEN("it returns 0")
            {
                REQUIRE(networkProxy.port() == 0);
            }

            AND_THEN("create return QNetworkProxy with port set to 0")
            {
                REQUIRE(networkProxy.create().port() == 0);
            }

            AND_WHEN("I set port to 8080")
            {
                networkProxy.setPort(8080);

                THEN("port is set to 8080")
                {
                    REQUIRE(networkProxy.port() == 8080);
                }

                AND_THEN("portChanged signal is emitted")
                {
                    REQUIRE(portChangedSpy.count() == 1);
                }

                AND_THEN("changed signal is emitted")
                {
                    REQUIRE(changedSpy.count() == 1);
                }

                AND_THEN("create return QNetworkProxy with port set to 8080")
                {
                    REQUIRE(networkProxy.create().port() == 8080);
                }

                AND_THEN("rawData contains one entry")
                {
                    REQUIRE(networkProxy.rawData().count() == 1);
                }
            }
        }
    }
}
