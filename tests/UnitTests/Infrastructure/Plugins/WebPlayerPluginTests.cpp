#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <MellowPlayer/Infrastructure/Plugins/WebPlayerPlugin.hpp>
#include <UnitTests/Domain/Plugins/Fakes/FakeWebPlayerScriptFactory.hpp>
#include <Mocks/SettingsStoreMock.hpp>
#include <UnitTests/Domain/Plugins/Fakes/FakePluginMetadataFactory.hpp>
#include <UnitTests/Infrastructure/System/Fakes/FakeIniFileFactory.hpp>
#include <QtCore/QDir>

using namespace MellowPlayer;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("WebPlayerPluginTests")
{
    GIVEN("A WebPlayerPlugin instance")
    {
        FakeIniFileFactory fakeIniFileFactory;
        FakeWebPlayerScriptFactory fakeScriptFactory;
        FakePluginMetadataFactory fakePluginMetadataFactory;
        auto settingsStoreMock = SettingsStoreMock::get();
        auto& settingsStore = settingsStoreMock.get();

        WebPlayerPlugin plugin(":/MellowPlayer/Domain/PluginTemplate",
                               fakeScriptFactory,
                               fakePluginMetadataFactory,
                               fakeIniFileFactory,
                               settingsStore);

        WHEN("load a valid plugin")
        {
            QString metadataPath = plugin.path() + QDir::separator() + "metadata.ini";
            QString pluginUrl = "https://fakeplayerplugin.org";;
            fakeScriptFactory.createValidScripts = true;
            QMap<QString, QVariant> iniFileData;
            iniFileData["url"] = pluginUrl;
            fakeIniFileFactory.iniFileContents[metadataPath] = iniFileData;

            plugin.load();

            THEN("webPlayerFactory is called with correct path")
            {
                QString integrationJsPath = plugin.path() + QDir::separator() +  "integration.js";
                REQUIRE(fakeScriptFactory.callsParam.at(0) == integrationJsPath);

                AND_THEN("a valid script is created")
                {
                    REQUIRE(plugin.script()->isValid());
                }
            }

            AND_THEN("pluginMetadataFactory is called")
            {
                REQUIRE(fakePluginMetadataFactory.callsParam.at(0) == metadataPath);

                AND_THEN("metadata are not empty")
                {
                    REQUIRE(!plugin.metadata()->name().isEmpty());
                    REQUIRE(!plugin.metadata()->author().isEmpty());
                    REQUIRE(!plugin.metadata()->authorUrl().isEmpty());
                    REQUIRE(!plugin.metadata()->version().isEmpty());
                    REQUIRE(!plugin.metadata()->logo().isEmpty());
                }
            }

            AND_THEN("iniFileFactory is called with correct path to read url")
            {
                REQUIRE(fakeIniFileFactory.callsParam.at(0).toStdString() == metadataPath.toStdString());

                AND_THEN("url is correctly set")
                {
                    REQUIRE(plugin.url() == pluginUrl);
                }
            }
        }

        WHEN("load an invalid plugin script")
        {
            fakeScriptFactory.createValidScripts = false;

            THEN("throws runtime_error")
            {
                REQUIRE_THROWS(plugin.load());
            }
        }
    }
}
