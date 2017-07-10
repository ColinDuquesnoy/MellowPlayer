#include <catch.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <QtTest/QSignalSpy>

USING_MELLOWPLAYER_NAMESPACE(Application)
using namespace fakeit;
using namespace std;

TEST_CASE("StreamingServicesTests", "[UnitTest]") {
    auto mock = StreamingServiceLoaderMock::get();
    StreamingServicesController streamingServices(mock.get());
    QSignalSpy addedSpy(&streamingServices, SIGNAL(added(StreamingService*)));
    streamingServices.load();

    SECTION("load called StreamingServiceLoader::load") {
        Verify(Method(mock, load)).Exactly(1);
        REQUIRE(streamingServices.getAll().count() > 1);
    };

    SECTION("added signal is emitted for each service loaded") {
        REQUIRE(addedSpy.count() > 1);
    }

    SECTION("get with valid service name") {
        REQUIRE(streamingServices.get("Deezer").getName() == "Deezer");
    };

    SECTION("get with unknown service name throws") {
        CHECK_THROWS(streamingServices.get("Unknown"));
    }

    SECTION("current service is initially empty") {
        REQUIRE(streamingServices.getCurrent() == nullptr);
    }

    SECTION("set current service ") {
        QSignalSpy spyCurrentChanged(&streamingServices, SIGNAL(currentChanged(StreamingService*)));
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        REQUIRE(streamingServices.getCurrent() != nullptr);
        REQUIRE(spyCurrentChanged.count() == 1);
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        REQUIRE(spyCurrentChanged.count() == 1);
    }

    SECTION("reload ") {
        addedSpy.clear();
        streamingServices.load();
        REQUIRE(addedSpy.count() == 0);
    }
}
