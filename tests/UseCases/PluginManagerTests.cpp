#include <catch.hpp>
#include <Mocks/PluginLoaderMock.hpp>
#include <MellowPlayer/UseCases/Plugins/PluginManager.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;
using namespace std;

TEST_CASE("PluginManager use the pluginLoader to get the list of plugins", "[PluginManager][UseCases]") {
    auto mock = PluginLoaderMock::basicMock();
    PluginManager pluginManager(mock.get());
    Verify(Method(mock, loadPlugins)).Exactly(1);
};

TEST_CASE("PluginManager can find a specific plugin", "[PluginManager][UseCases]") {
    auto mock = PluginLoaderMock::basicMock();
    PluginManager pluginManager(mock.get());

    SECTION("Find plugin by name") {
        REQUIRE(pluginManager.plugin("Deezer").name == "Deezer");
    }

    SECTION("Find unknown plugin should throw an exception") {
        CHECK_THROWS(pluginManager.plugin("Unknown"));
    }
};
