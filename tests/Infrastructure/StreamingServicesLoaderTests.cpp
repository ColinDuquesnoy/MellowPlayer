#include <catch.hpp>
#include <fakeit.hpp>

#include <MellowPlayer/Infrastructure/System/StreamingServicesLoader.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("StreamingServicesLoader load plugins from CMAKE_SOURCE_DIR", "[StreamingServicesLoader][Infrastructure][IntegrationTest]") {
    StreamingServicesLoader pluginLoader;
    StreamingServicesList plugins = pluginLoader.load();
    REQUIRE(plugins.count() > 1);
}

