#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <Mocks/SettingsProviderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)


TEST_CASE("StreamingServiceLoaderTests") {
    StreamingServiceLoader pluginLoader;

    SECTION("load") {
        auto plugins = pluginLoader.load();
        REQUIRE(plugins.count() > 1);
    }
}
