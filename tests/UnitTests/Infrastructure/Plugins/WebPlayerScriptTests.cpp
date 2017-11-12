#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Plugins/WebPlayerScript.hpp>
#include <Mocks/SettingsStoreMock.hpp>
#include <MellowPlayer/Infrastructure/System/FileFactory.hpp>
#include <MellowPlayer/Infrastructure/System/IFile.hpp>

using namespace std;
using namespace fakeit;
using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;

SCENARIO("WebPlayerScriptTests")
{
    GIVEN("A fake player script file")
    {
        QString integrationJsPath = ":/MellowPlayer/Domain/PluginTemplate/integration.js";
        Mock<IFile> integrationJsFileMock;
        When(Method(integrationJsFileMock, exists)).Return(true);
        When(Method(integrationJsFileMock, open)).Return(true);
        When(Method(integrationJsFileMock, path)).Return(integrationJsPath);
        auto settingsStoreMock = SettingsStoreMock::get();
        auto& settingsStore = settingsStoreMock.get();

        shared_ptr<IFile> file(&integrationJsFileMock.get(), [](IFile*) {});
        WebPlayerScript script(file);

        WHEN("load a valid plugin")
        {
            QString expectedCode = "function update\n"
                    "function play\n"
                    "function pause\n"
                    "function goNext\n"
                    "function goPrevious\n"
                    "function setVolume\n"
                    "function addToFavorites\n"
                    "function removeFromFavorites\n"
                    "function seekToPosition\n";
            When(Method(integrationJsFileMock, content)).Return(expectedCode);
            script.load();

            THEN("script code is correctly loaded")
            {
                REQUIRE(script.code() == expectedCode);
            }
        }

        WHEN("load an invalid plugin script")
        {
            QString invalidCode = "invalid code";
            When(Method(integrationJsFileMock, content)).Return(invalidCode);

            THEN("throws runtime_error")
            {
                REQUIRE_THROWS(script.load());
            }
        }
    }
}
