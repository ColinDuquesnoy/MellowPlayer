#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/Infrastructure/StreamingServicePluginLoader.hpp>
#include <Mocks/SettingsProviderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)


TEST_CASE("PluginLoaderTests") {
    StreamingServicePluginLoader pluginLoader;

    SECTION("load") {
        auto plugins = pluginLoader.load();
        REQUIRE(plugins.count() > 1);
    }
}

