#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include <MellowPlayer/Infrastructure/PluginLoader.hpp>
#include <Mocks/SettingsProviderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)


TEST_CASE("PluginLoaderTests") {
    PluginLoader pluginLoader;

    SECTION("load") {
        auto plugins = pluginLoader.load();
        REQUIRE(plugins.count() > 1);
    }
}

