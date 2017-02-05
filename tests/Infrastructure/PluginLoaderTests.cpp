#include <catch.hpp>
#include <fakeit.hpp>

#include <MellowPlayer/Infrastructure/Plugins/PluginLoader.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("PluginLoader load plugins from CMAKE_SOURCE_DIR", "[PluginLoader][Infrastructure][IntegrationTest]") {
    PluginLoader pluginLoader(LoggingManager::instance());
    PluginList plugins = pluginLoader.loadPlugins();
    REQUIRE(plugins.count() > 1);
}

