#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceLoader.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceWatcher.hpp>
#include <QtTest/QSignalSpy>
#include <catch/catch.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

TEST_CASE("StreamingServicesTests")
{
    FakeStreamingServiceLoader streamingServiceLoader;
    FakeStreamingServiceWatcher streamingServiceWatcher;
    StreamingServices streamingServices(streamingServiceLoader, streamingServiceWatcher);
    QSignalSpy addedSpy(&streamingServices, SIGNAL(added(StreamingService*)));
    streamingServices.load();

    SECTION("load called StreamingServiceLoader::load and watch every new service")
    {
        REQUIRE(streamingServices.toList().count() == 4);
        REQUIRE(streamingServiceWatcher.watchedServices.count() == streamingServices.toList().count());
    };

    SECTION("added signal is emitted for each service loaded")
    {
        REQUIRE(addedSpy.count() > 1);
    }

    SECTION("get with valid service name")
    {
        REQUIRE(streamingServices.get("Deezer").name() == "Deezer");
    };

    SECTION("get with unknown service name throws")
    {
        CHECK_THROWS(streamingServices.get("Unknown"));
    }

    SECTION("current service is initially empty")
    {
        REQUIRE(streamingServices.current() == nullptr);
    }

    SECTION("set current service ")
    {
        QSignalSpy spyCurrentChanged(&streamingServices, SIGNAL(currentChanged(StreamingService*)));
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        REQUIRE(streamingServices.current() != nullptr);
        REQUIRE(spyCurrentChanged.count() == 1);
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        REQUIRE(spyCurrentChanged.count() == 1);
    }

    SECTION("reload ")
    {
        addedSpy.clear();
        streamingServices.load();
        REQUIRE(addedSpy.count() == 0);
    }
}
