#include "Mocks/FakeHttpClient.hpp"
#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <MellowPlayer/Infrastructure/Updater/Github/LatestGithubReleaseQuerier.hpp>

using namespace MellowPlayer::Domain;

SCENARIO("get latest github release")
{
    GIVEN("the stable update channel")
    {
        FakeHttpClient fakeHttpClient;
        LatestGithubReleaseQuerier querier(fakeHttpClient);
        querier.setChannel(UpdateChannel::Stable);

        const Release* latestRelease = nullptr;
        QObject::connect(&querier, &LatestGithubReleaseQuerier::latestReceived, [&](const Release* release) { latestRelease = release; });
        REQUIRE(latestRelease == nullptr);

        WHEN("query is called")
        {
            querier.query();

            THEN("latest stable release is retrieved")
            {
                REQUIRE(latestRelease != nullptr);
                REQUIRE(latestRelease->name().toStdString() == "2.2.5");
            }
        }
    }

    GIVEN("the beta update channel")
    {
        FakeHttpClient networkAccessManagerMock;
        LatestGithubReleaseQuerier querier(networkAccessManagerMock);
        querier.setChannel(UpdateChannel::Beta);

        const Release* latestRelease = nullptr;
        QObject::connect(&querier, &LatestGithubReleaseQuerier::latestReceived, [&](const Release* release) { latestRelease = release; });
        REQUIRE(latestRelease == nullptr);

        WHEN("query is called")
        {
            querier.query();

            THEN("latest beta release is retrieved")
            {
                REQUIRE(latestRelease != nullptr);
                REQUIRE(latestRelease->name().toStdString() == "2.95.0");
            }
        }
    }

    GIVEN("the continuous update channel")
    {
        FakeHttpClient networkAccessManagerMock;
        LatestGithubReleaseQuerier querier(networkAccessManagerMock);
        querier.setChannel(UpdateChannel::Continuous);

        const Release* latestRelease = nullptr;
        QObject::connect(&querier, &LatestGithubReleaseQuerier::latestReceived, [&](const Release* release) { latestRelease = release; });
        REQUIRE(latestRelease == nullptr);

        WHEN("query is called")
        {
            querier.query();

            THEN("latest stable release is retrieved")
            {
                REQUIRE(latestRelease != nullptr);
                REQUIRE(latestRelease->name().toStdString() == "Continuous");
            }
        }
    }
}
