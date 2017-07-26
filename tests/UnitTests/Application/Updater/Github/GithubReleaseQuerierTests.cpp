#include "Mocks/FakeHttpClient.hpp"
#include "catch.hpp"
#include <MellowPlayer/Application/Updater/Github/GithubReleaseQuerier.hpp>

using namespace MellowPlayer::Application;

SCENARIO("get latest github release")
{
    GIVEN("the stable update channel")
    {
        FakeHttpClient fakeHttpClient;
        GithubReleaseQuerier querier(fakeHttpClient);
        querier.setChannel(UpdateChannel::Stable);

        const Release* latestRelease = nullptr;
        QObject::connect(&querier, &GithubReleaseQuerier::latestReceived, [&](const Release* release) { latestRelease = release; });
        REQUIRE(latestRelease == nullptr);

        WHEN("getLatest is called")
        {
            querier.getLatest();

            THEN("latest stable release is retrieved")
            {
                REQUIRE(latestRelease != nullptr);
                REQUIRE(latestRelease->getName().toStdString() == "2.2.5");
            }
        }
    }

    GIVEN("the beta update channel")
    {
        FakeHttpClient networkAccessManagerMock;
        GithubReleaseQuerier querier(networkAccessManagerMock);
        querier.setChannel(UpdateChannel::Beta);

        const Release* latestRelease = nullptr;
        QObject::connect(&querier, &GithubReleaseQuerier::latestReceived, [&](const Release* release) { latestRelease = release; });
        REQUIRE(latestRelease == nullptr);

        WHEN("getLatest is called")
        {
            querier.getLatest();

            THEN("latest beta release is retrieved")
            {
                REQUIRE(latestRelease != nullptr);
                REQUIRE(latestRelease->getName().toStdString() == "2.95.0");
            }
        }
    }

    GIVEN("the continuous update channel")
    {
        FakeHttpClient networkAccessManagerMock;
        GithubReleaseQuerier querier(networkAccessManagerMock);
        querier.setChannel(UpdateChannel::Continuous);

        const Release* latestRelease = nullptr;
        QObject::connect(&querier, &GithubReleaseQuerier::latestReceived, [&](const Release* release) { latestRelease = release; });
        REQUIRE(latestRelease == nullptr);

        WHEN("getLatest is called")
        {
            querier.getLatest();

            THEN("latest stable release is retrieved")
            {
                REQUIRE(latestRelease != nullptr);
                REQUIRE(latestRelease->getName().toStdString() == "Continuous");
            }
        }
    }
}
