#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <catch/catch.hpp>
#include <QtTest/qtestsystem.h>

using namespace std;
using namespace MellowPlayer::Infrastructure;

class LocalSocketFactory: public IFactory<ILocalSocket>
{
public:
    std::unique_ptr<ILocalSocket> create() const override
    {
        return make_unique<LocalSocket>();
    }
};

SCENARIO("LocalServer and LocalSocket integration tests")
{
    GIVEN("A local server and a local socket")
    {
        QString serverName = "MellowPlayerLocalServerIntegrationTests";
        LocalSocketFactory factory;
        LocalServer server(factory, serverName);
        server.listen();

        REQUIRE(server.isListening());
        REQUIRE(!server.serverSocketFilePath().isEmpty());

        LocalSocket socket;
        unique_ptr<ILocalSocket> newConnection = nullptr;
        QObject::connect(&server, &ILocalServer::newConnection, [&]() {
            newConnection = server.nextPendingConnection();
        });

        WHEN("I connect the socket to the server")
        {
            socket.connectToServer(serverName, QIODevice::WriteOnly);

            QTest::qWait(1000);

            THEN("a new connection has been received")
            {
                REQUIRE(newConnection != nullptr);
            }

            AND_WHEN("writing on the socket")
            {
                QString receivedData;

                QObject::connect(newConnection.get(), &ILocalSocket::readyRead, [&]() {
                    receivedData = newConnection->readAll();
                });
                socket.write("foo\n");

                QTest::qWait(1000);

                THEN("data is received on the server")
                {
                   REQUIRE(receivedData == "foo\n");
                }

                AND_WHEN("I disconnect the socket from server")
                {
                    socket.disconnectFromServer();
                    
                    THEN("I cannot write to the socket")
                    {
                        REQUIRE_THROWS(socket.write("data"));
                    }
                }
            }

            AND_WHEN("I close the server")
            {
                server.close();

                REQUIRE(!server.isListening());
            }
        }
    }
}
