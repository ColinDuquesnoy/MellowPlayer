#include <catch.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePluginMetadata.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

TEST_CASE("PluginTests", "[UnitTest]") {
    SECTION("StreamingServicePlugin.DefaultCtor") {
        StreamingServicePluginMetadata plugin;

        REQUIRE(plugin.author == "");
        REQUIRE(plugin.authorWebsite == "");
        REQUIRE(plugin.color == "");
        REQUIRE(plugin.logoPath == "");
        REQUIRE(plugin.name == "");
        REQUIRE(plugin.url == "");
        REQUIRE(plugin.script == "");
        REQUIRE(plugin.version == "");
    }

    SECTION("StreamingServicePlugin.isValid") {
        StreamingServicePluginMetadata plugin;

        REQUIRE(!plugin.isValid());
        plugin.url = "https://deezer.com";
        REQUIRE(!plugin.isValid());
        plugin.name = "Deezer";
        REQUIRE(!plugin.isValid());
        plugin.script = "function test() { }";
        REQUIRE(plugin.isValid());
    }

    SECTION("StreamingServicePlugin.operator==") {
        StreamingServicePluginMetadata plugin;
        StreamingServicePluginMetadata test;

        REQUIRE(plugin == test);
        plugin.url = "https://deezer.com";
        REQUIRE(plugin != test);
        plugin.url = "";
        plugin.name = "Deezer";
        REQUIRE(plugin != test);
    }
}