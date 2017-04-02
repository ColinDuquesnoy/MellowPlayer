#include <catch.hpp>
#include <MellowPlayer/Entities/PluginMetadata.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

TEST_CASE("PluginTests") {
    SECTION("Plugin.DefaultCtor") {
        PluginMetadata plugin;

        REQUIRE(plugin.author == "");
        REQUIRE(plugin.authorWebsite == "");
        REQUIRE(plugin.color == "");
        REQUIRE(plugin.logoPath == "");
        REQUIRE(plugin.name == "");
        REQUIRE(plugin.url == "");
        REQUIRE(plugin.script == "");
        REQUIRE(plugin.version == "");
    }

    SECTION("Plugin.isValid") {
        PluginMetadata plugin;

        REQUIRE(!plugin.isValid());
        plugin.url = "https://deezer.com";
        REQUIRE(!plugin.isValid());
        plugin.name = "Deezer";
        REQUIRE(!plugin.isValid());
        plugin.script = "function test() { }";
        REQUIRE(plugin.isValid());
    }

    SECTION("Plugin.operator==") {
        PluginMetadata plugin;
        PluginMetadata test;

        REQUIRE(plugin == test);
        plugin.url = "https://deezer.com";
        REQUIRE(plugin != test);
        plugin.url = "";
        plugin.name = "Deezer";
        REQUIRE(plugin != test);
    }
}