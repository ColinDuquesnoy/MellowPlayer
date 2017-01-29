#include <catch.hpp>
#include <MellowPlayer/Entities.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
using namespace std;

TEST_CASE("Plugin.DefaultCtor", "[Plugin]") {
    Plugin plugin;

    REQUIRE(plugin.author == "");
    REQUIRE(plugin.authorWebsite == "");
    REQUIRE(plugin.color == "");
    REQUIRE(plugin.logo.isNull());
    REQUIRE(plugin.name == "");
    REQUIRE(plugin.url == "");
    REQUIRE(plugin.script == "");
    REQUIRE(plugin.version == "");
}
