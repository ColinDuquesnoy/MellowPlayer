#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include <MellowPlayer/Infrastructure/PluginLoader.hpp>
#include <Mocks/ApplicationSettingsMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)


TEST_CASE("PluginLoaderTests", "[IntegrationTest]") {
    PluginLoader pluginLoader;
    PluginList plugins = pluginLoader.load();
    REQUIRE(plugins.count() > 1);
}

