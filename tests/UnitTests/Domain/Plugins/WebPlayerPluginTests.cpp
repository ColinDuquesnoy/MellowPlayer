#include <MellowPlayer/Domain/Plugins/WebPlayerPlugin.hpp>
#include <catch.hpp>
#include <fakeit/fakeit.hpp>
#include "Fakes/FakePluginMetadata.hpp"
#include "Fakes/FakeWebPlayerScript.hpp"

using namespace fakeit;
using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

class FakeWebPlayerPlugin: public WebPlayerPlugin
{
public:
    void load() override
    {
        metadata_ = make_shared<FakePluginMetadata>("FooBar", "1.0.0", "Foo", "https://foo.org", "logo.svg");
        metadata_->load();
        path_ = "/path/to/plugin";
        url_ = "https://webplayerservice.com";
        isEnabled_ = true;
        script_ = make_shared<FakeWebPlayerScript>("code");
    }
};

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