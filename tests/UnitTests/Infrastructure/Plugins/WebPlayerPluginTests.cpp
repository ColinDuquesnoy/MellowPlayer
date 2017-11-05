#include <QtCore/QDir>
#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <MellowPlayer/Infrastructure/Plugins/WebPlayerPlugin.hpp>
#include <Mocks/SettingsStoreMock.hpp>
#include <UnitTests/Infrastructure/System/Fakes/FakeIniFileFactory.hpp>
#include <UnitTests/Infrastructure/System/Fakes/FakeFileFactory.hpp>
#include <iostream>

using namespace std;
using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("WebPlayerPluginTests")
{
    GIVEN("A WebPlayerPlugin instance")
    {
        auto settingsStoreMock = SettingsStoreMock::get();
        auto& settingsStore = settingsStoreMock.get();

        QString pluginDir = "/path/to/plugin";
        QString metadataPath = pluginDir + QDir::separator() + "metadata.ini";
        QString integrationJsPath = pluginDir + QDir::separator() +  "integration.js";

        WHEN("load a valid plugin")
        {
            FakeFileFactory fileFactory;
            FakeIniFileFactory iniFileFactory;
            fileFactory.fileContents[integrationJsPath] = "function update\n"
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
            iniFileFactory.iniFileContents[metadataPath] = iniFileData;

            WebPlayerPlugin plugin(pluginDir, fileFactory, iniFileFactory, settingsStore);

            try {
                plugin.load();
            }
            catch (std::runtime_error& e)
            {
                cout << "exception was: " << e.what() << endl;
                throw e;
            }

            THEN("fileFactory is called with integration.js path")
            {
                REQUIRE(fileFactory.callsParam.at(0) == integrationJsPath);

                AND_THEN("a valid script is created")
                {
                    REQUIRE(plugin.script()->isValid());
                }
            }

            AND_THEN("iniFileFactory is called with metads")
            {
                REQUIRE(iniFileFactory.callsParam.at(0) == metadataPath);

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
                REQUIRE(iniFileFactory.callsParam.at(1).toStdString() == metadataPath.toStdString());

                AND_THEN("url is correctly set")
                {
                    REQUIRE(plugin.url() == pluginUrl);
                }
            }
        }

        WHEN("load an invalid plugin script")
        {
            FakeFileFactory fileFactory;
            FakeIniFileFactory iniFileFactory;
            fileFactory.fileContents[integrationJsPath] = "invalid";
            WebPlayerPlugin plugin("plugin",
                                   fileFactory,
                                   iniFileFactory,
                                   settingsStore);

            THEN("throws runtime_error")
            {
                REQUIRE_THROWS(plugin.load());
            }
        }
    }
}
