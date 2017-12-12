#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace fakeit;
using namespace std;

TEST_CASE("StreamingServicesControllerTests", "[UnitTest]")
{
    auto loaderMock = StreamingServiceLoaderMock::get();
    auto watcherMock = StreamingServiceWatcherMock::get();
    StreamingServices streamingServices(loaderMock.get(), watcherMock.get());
    QSignalSpy addedSpy(&streamingServices, SIGNAL(added(StreamingService*)));
    streamingServices.load();

    SECTION("load called StreamingServiceLoader::load and watch every new service")
    {
        REQUIRE(streamingServices.toList().count() > 1);
        Verify(Method(loaderMock, load)).Exactly(1);
        Verify(Method(watcherMock, watch)).Exactly(streamingServices.toList().count());
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
