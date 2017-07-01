#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <Mocks/SettingsProviderMock.hpp>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)


TEST_CASE("StreamingServiceLoaderTests") {
    StreamingServiceLoader loader;

    SECTION("load") {
        auto services = loader.load();
        REQUIRE(services.count() > 1);
    }
}
