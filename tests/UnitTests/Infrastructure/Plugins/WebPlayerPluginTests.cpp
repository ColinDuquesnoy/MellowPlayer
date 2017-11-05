#include <QtCore/QDir>
#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <MellowPlayer/Infrastructure/Plugins/WebPlayerPlugin.hpp>
#include <Mocks/SettingsStoreMock.hpp>
#include <UnitTests/Infrastructure/System/Fakes/FakeIniFileFactory.hpp>
#include <UnitTests/Infrastructure/System/Fakes/FakeFileFactory.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("WebPlayerPluginTests")
{
    GIVEN("A WebPlayerPlugin instance")
    {
        FakeFileFactory fakeFileFactory;
        FakeIniFileFactory fakeIniFileFactory;
        auto settingsStoreMock = SettingsStoreMock::get();
        auto& settingsStore = settingsStoreMock.get();

        WebPlayerPlugin plugin(":/MellowPlayer/Domain/PluginTemplate",
                               fakeFileFactory,
                               fakeIniFileFactory,
                               settingsStore);

        QString metadataPath = plugin.path() + QDir::separator() + "metadata.ini";
        QString integrationJsPath = plugin.path() + QDir::separator() +  "integration.js";

        WHEN("load a valid plugin")
        {
            fakeFileFactory.fileContents[integrationJsPath] = "function update\n"
                                                              "function play\n"
                                                              "function pause\n"
                                                              "function goNext\n"
                                                              "function goPrevious\n"
                                                              "function setVolume\n"
                                                              "function addToFavorites\n"
                                                              "function removeFromFavorites\n"
                                                              "function seekToPosition\n";
            QString pluginUrl = "https://fakeplayerplugin.org";;
            QMap<QString, QVariant> iniFileData;
            iniFileData["url"] = pluginUrl;
            iniFileData["author"] = "authorName";
            iniFileData["author_website"] = "authorUrl";
            iniFileData["icon"] = "logo.svg";
            iniFileData["name"] = "pluginName";
            iniFileData["version"] = "pluginVersion";
            fakeIniFileFactory.iniFileContents[metadataPath] = iniFileData;

            plugin.load();

            THEN("fileFactory is called with correct path")
            {
                REQUIRE(fakeFileFactory.callsParam.at(0) == integrationJsPath);

                AND_THEN("a valid script is created")
                {
                    REQUIRE(plugin.script()->isValid());
                }
            }

            AND_THEN("pluginMetadataFactory is called")
            {
                REQUIRE(fakeIniFileFactory.callsParam.at(0) == metadataPath);

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
                REQUIRE(fakeIniFileFactory.callsParam.at(1).toStdString() == metadataPath.toStdString());

                AND_THEN("url is correctly set")
                {
                    REQUIRE(plugin.url() == pluginUrl);
                }
            }
        }

        WHEN("load an invalid plugin script")
        {
            fakeFileFactory.fileContents[integrationJsPath] = "invalid";

            THEN("throws runtime_error")
            {
                REQUIRE_THROWS(plugin.load());
            }
        }
    }
}
