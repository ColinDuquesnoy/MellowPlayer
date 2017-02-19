#include <catch.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <MellowPlayer/UseCases/StreamingServicesManager.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;
using namespace std;

TEST_CASE("StreamingServicesManagerTests") {
    auto mock = StreamingServiceLoaderMock::get();
    StreamingServicesManager streamingServicesManager(mock.get());
    QSignalSpy serviceAddedSpy(&streamingServicesManager, SIGNAL(serviceAdded(StreamingService*)));
    streamingServicesManager.load();

    SECTION("load called StreamingServicesLoader::load") {
        Verify(Method(mock, load)).Exactly(1);
        REQUIRE(streamingServicesManager.getServices().count() > 1);
    };

    SECTION("serviceAdded signal is emitted for each service loaded") {
        REQUIRE(serviceAddedSpy.count() > 1);
    }

    SECTION("getService with valid service name") {
        REQUIRE(streamingServicesManager.getService("Deezer").getName() == "Deezer");
    };

    SECTION("getService with unknown service name throws") {
        CHECK_THROWS(streamingServicesManager.getService("Unknown"));
    }

    SECTION("current service is initially empty") {
        REQUIRE(streamingServicesManager.getCurrentService() == nullptr);
    }

    SECTION("set current service ") {
        QSignalSpy currentServiceChangedSignal(&streamingServicesManager,
                                               SIGNAL(currentServiceChanged(StreamingService*)));
        streamingServicesManager.setCurrentService(&streamingServicesManager.getService("Deezer"));
        REQUIRE(streamingServicesManager.getCurrentService() != nullptr);
        REQUIRE(currentServiceChangedSignal.count() == 1);
        streamingServicesManager.setCurrentService(&streamingServicesManager.getService("Deezer"));
        REQUIRE(currentServiceChangedSignal.count() == 1);
    }

    SECTION("reload ") {
        serviceAddedSpy.clear();
        streamingServicesManager.load();
        REQUIRE(serviceAddedSpy.count() == 0);
    }
}
