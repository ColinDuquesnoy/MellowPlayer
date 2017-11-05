#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <MellowPlayer/Infrastructure/Plugins/WebPlayerPlugin.hpp>
#include <UnitTests/Domain/Plugins/Fakes/FakeWebPlayerScriptFactory.hpp>
#include <Mocks/SettingsStoreMock.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Domain::Tests;

SCENARIO("WebPlayerPluginTests")
{
    GIVEN("A WebPlayerPlugin instance")
    {
        FakeWebPlayerScriptFactory fakeScriptFactory;
        auto settingsStoreMock = SettingsStoreMock::get();
        auto& settingsStore = settingsStoreMock.get();

        WebPlayerPlugin plugin(":/MellowPlayer/Domain/PluginTemplate", fakeScriptFactory, settingsStore);

        WHEN("load a valid plugin")
        {
            plugin.load();
            QString integrationJsPath = plugin.path() + "/integration.js";

            THEN("webPlayerFactory is called with correct path")
            {
                REQUIRE(fakeScriptFactory.callsParam.at(0) == integrationJsPath);

                AND_THEN("a valid script is created")
                {
                    REQUIRE(plugin.script()->isValid());
                }
            }
        }
    }
}
