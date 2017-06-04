#include <catch.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServiceMetadata.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

TEST_CASE("StreamingServiceMetadataTests", "[UnitTest]") {
    SECTION("StreamingService.DefaultCtor") {
        StreamingServiceMetadata plugin;

        REQUIRE(plugin.author == "");
        REQUIRE(plugin.authorWebsite == "");
        REQUIRE(plugin.color == "");
        REQUIRE(plugin.logoPath == "");
        REQUIRE(plugin.name == "");
        REQUIRE(plugin.url == "");
        REQUIRE(plugin.script == "");
        REQUIRE(plugin.version == "");
    }

    SECTION("StreamingService.isValid") {
        StreamingServiceMetadata plugin;

        REQUIRE(!plugin.isValid());
        plugin.url = "https://deezer.com";
        REQUIRE(!plugin.isValid());
        plugin.name = "Deezer";
        REQUIRE(!plugin.isValid());
        plugin.script = "function test() { }";
        REQUIRE(plugin.isValid());
    }

    SECTION("StreamingService.operator==") {
        StreamingServiceMetadata plugin;
        StreamingServiceMetadata test;

        REQUIRE(plugin == test);
        plugin.url = "https://deezer.com";
        REQUIRE(plugin != test);
        plugin.url = "";
        plugin.name = "Deezer";
        REQUIRE(plugin != test);
    }
}