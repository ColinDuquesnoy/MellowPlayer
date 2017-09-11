#include <MellowPlayer/Infrastructure/Updater/HttpClient.hpp>
#include <QtTest/qtestsystem.h>
#include <catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("HttpClient get github API response")
{
    HttpClient client;

    GIVEN("an initial state and the most basic github query url")
    {
        bool replyReceived = false;
        QByteArray replyData;

        client.connect(&client, &HttpClient::replyReceived, [&](const QByteArray& data) {
            replyReceived = true;
            replyData = data;
        });

        WHEN("a get request is send")
        {
            client.get("https://api.github.com/");
            REQUIRE(!replyReceived);
            REQUIRE(replyData.isEmpty());

            THEN("it receives a non empty response")
            {
                QTest::qWait(1000);
                if (replyReceived)
                    REQUIRE(!replyData.isEmpty());
            }
        }
    }
}
