#include <MellowPlayer/Infrastructure/Plugins/WebPlayerScript.hpp>
#include <UnitTests/Infrastructure/System/Fakes/FakeFileFactory.hpp>
#include <Mocks/SettingsStoreMock.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("WebPlayerScriptTests")
{
    GIVEN("A WebPlayerScript instance")
    {
        FakeFileFactory fakeFileFactory;
        auto settingsStoreMock = SettingsStoreMock::get();
        auto& settingsStore = settingsStoreMock.get();

        WHEN("load a valid plugin")
        {
            WebPlayerScript script(fakeFileFactory, ":/MellowPlayer/Domain/PluginTemplate/integration.js" );
            QString integrationJsPath =  script.path();
            QString integrationJsContent =  "function update\n"
                                            "function play\n"
                                            "function pause\n"
                                            "function goNext\n"
                                            "function goPrevious\n"
                                            "function setVolume\n"
                                            "function addToFavorites\n"
                                            "function removeFromFavorites\n"
                                            "function seekToPosition\n";
            fakeFileFactory.fileContents[integrationJsPath] = integrationJsContent;
            script.load();

            THEN("create a file to load integration.js")
            {
                REQUIRE(fakeFileFactory.callsParam.at(0) == integrationJsPath);

                AND_THEN("script code is correctly loaded")
                {
                    REQUIRE(script.code() == integrationJsContent);
                }
            }
        }
    }
}
