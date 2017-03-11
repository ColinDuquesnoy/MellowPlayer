#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Infrastructure/PluginLoader.hpp>
#include <Mocks/ApplicationSettingsMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("PluginLoader load plugins from CMAKE_SOURCE_DIR", "[PluginLoader][Infrastructure][IntegrationTest]") {
    PluginLoader pluginLoader;
    PluginList plugins = pluginLoader.load();
    REQUIRE(plugins.count() > 1);
}

