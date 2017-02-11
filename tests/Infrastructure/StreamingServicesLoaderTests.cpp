#include <catch.hpp>
#include <fakeit.hpp>

#include <MellowPlayer/Infrastructure/StreamingServicesLoader.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("StreamingServicesLoader load plugins from CMAKE_SOURCE_DIR", "[StreamingServicesLoader][Infrastructure][IntegrationTest]") {
    StreamingServicesLoader pluginLoader(LoggingManager::instance());
    StreamingServicesList plugins = pluginLoader.load();
    REQUIRE(plugins.count() > 1);
}

