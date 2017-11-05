#include <MellowPlayer/Domain/Plugins/WebPlayerPlugin.hpp>
#include <catch.hpp>
#include "Fakes/FakeWebPlayerPlugin.hpp"

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

SCENARIO("WebPlayerPluginTests")
{
    GIVEN("a FakeWebPlayerPlugin")
    {
        FakeWebPlayerPlugin webPlayerPlugin;

        WHEN("load")
        {
            webPlayerPlugin.load();

            THEN("url is not empty")
            {
                REQUIRE(!webPlayerPlugin.url().isEmpty());
            }

            AND_THEN("script is not null")
            {
                REQUIRE(webPlayerPlugin.script() != nullptr);
            }

            AND_THEN("metadata is not null")
            {
                REQUIRE(webPlayerPlugin.metadata() != nullptr);
            }

            AND_THEN("path is not empty")
            {
                REQUIRE(!webPlayerPlugin.path().isEmpty());
            }

            AND_THEN("isEnabled")
            {
                REQUIRE(webPlayerPlugin.isEnabled());
            }
        }

    }
}