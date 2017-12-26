#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
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

        REQUIRE(!networkProxy.isValid());

        WHEN("I call isEnabled")
        {
            THEN("it returns false")
            {
                REQUIRE(!networkProxy.isEnabled());
            }

            AND_THEN("proxy is still not valid")
            {
                REQUIRE(!networkProxy.isValid());
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

                AND_THEN("create return a QNetworkProxy with type set to DefaultProxy")
                {
                    REQUIRE(networkProxy.create().type() == QNetworkProxy::DefaultProxy);
                }

                AND_THEN("rawData is correct")
                {
                    REQUIRE(networkProxy.rawData()["enabled"].toBool());
                }
            }
        }

        WHEN("I call hostName")
        {
            THEN("it returns an empty string")
            {
                REQUIRE(networkProxy.hostName().isEmpty());
            }

            AND_THEN("proxy is still not valid")
            {
                REQUIRE(!networkProxy.isValid());
            }

            AND_THEN("create return QNetworkProxy with empty host")
            {
                REQUIRE(networkProxy.create().hostName().isEmpty());
            }

            AND_WHEN("I set hostName to 192.168.0.1")
            {
                QString hostName = "192.168.0.1";
                networkProxy.setHostName(hostName);

                THEN("hostName is correctly set")
                {
                    REQUIRE(networkProxy.hostName() == hostName);
                }

                AND_THEN("hostNameChanged signal is emitted")
                {
                    REQUIRE(hostNameChangedSpy.count() == 1);
                }

                AND_THEN("changed signal is emitted")
                {
                    REQUIRE(changedSpy.count() == 1);
                }

                AND_THEN("create return QNetworkProxy with empty host name")
                {
                    REQUIRE(networkProxy.create().hostName().isEmpty());
                }

                AND_THEN("rawData is correct")
                {
                    REQUIRE(networkProxy.rawData()["hostName"].toString() == hostName);
                }
            }
        }

        WHEN("I call port")
        {
            THEN("it returns 0")
            {
                REQUIRE(networkProxy.port() == 0);
            }

            AND_THEN("proxy is still not valid")
            {
                REQUIRE(!networkProxy.isValid());
            }

            AND_THEN("create return QNetworkProxy with port set to 0")
            {
                REQUIRE(networkProxy.create().port() == 0);
            }

            AND_WHEN("I set port to 8080")
            {
                int port = 42;
                networkProxy.setPort(port);

                THEN("port is correctly set")
                {
                    REQUIRE(networkProxy.port() == port);
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
                    REQUIRE(networkProxy.create().port() == 0);
                }

                AND_THEN("rawData is correct")
                {
                    REQUIRE(networkProxy.rawData()["port"].toInt() == port);
                }
            }
        }

        WHEN("I set all mandatory properties")
        {
            QString hostName = "103.60.137.2";
            int port = 270;
            networkProxy.setEnabled(true);
            networkProxy.setHostName(hostName);
            networkProxy.setPort(port);

            THEN("Network proxy is valid")
            {
                REQUIRE(networkProxy.isValid());
            }

            AND_WHEN("I create a QNetworkProxy")
            {
                QNetworkProxy qNetworkProxy = networkProxy.create();

                THEN("QNetworkProxy type is set to HttpProxy")
                {
                    REQUIRE(qNetworkProxy.type() == QNetworkProxy::HttpProxy);
                }

                AND_THEN("Hostname is correctly configured")
                {
                    REQUIRE(qNetworkProxy.hostName() == hostName);
                }

                AND_THEN("Port is correctly configured")
                {
                    REQUIRE(qNetworkProxy.port() == port);
                }
            }
        }
    }

    GIVEN("A valid QVariantMap")
    {
        QVariantMap rawData;
        rawData["enabled"] = true;
        rawData["hostName"] = "foo";
        rawData["port"] = 42;

        WHEN("I create a NetworkProxy instance")
        {
            NetworkProxy networkProxy(rawData);

            THEN("isEnabled is correctly initialized")
            {
                REQUIRE(networkProxy.isEnabled() == rawData["enabled"]);
            }

            AND_THEN("hostName is correctly initialized")
            {
                REQUIRE(networkProxy.hostName() == rawData["hostName"]);
            }

            AND_THEN("port is correctly initialized")
            {
                REQUIRE(networkProxy.port() == rawData["port"]);
            }
        }
    }

    GIVEN("A valid QNetworkProxy")
    {
        QNetworkProxy qNetworkProxy;
        qNetworkProxy.setHostName("foo");
        qNetworkProxy.setPort(42);

        WHEN("I create a NetworkProxy instance")
        {
            NetworkProxy networkProxy(qNetworkProxy);

            THEN("isEnabled is set to true")
            {
                REQUIRE(networkProxy.isEnabled() == true);
            }

            AND_THEN("hostName is correctly initialized")
            {
                REQUIRE(networkProxy.hostName() == qNetworkProxy.hostName());
            }

            AND_THEN("port is correctly initialized")
            {
                REQUIRE(networkProxy.port() == qNetworkProxy.port());
            }
        }
    }
}
