#include <TestMacros.hpp>
#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <MellowPlayer/Infrastructure/Plugins/WebPlayerPlugin.hpp>
#include <MellowPlayer/Infrastructure/System/FileFactory.hpp>
#include <MellowPlayer/Infrastructure/System/IniFileFactory.hpp>
#include <Mocks/SettingsStoreMock.hpp>
#include <QDir>

using namespace fakeit;
using namespace std;
using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;

SCENARIO("WebPlayerPluginTests")
{
    GIVEN("a ") {
        auto settingsStoreMock = SettingsStoreMock::get();
        auto& settingsStore = settingsStoreMock.get();

        QString pluginDir = "/path/to/plugin";
        QString metadataPath = pluginDir + QDir::separator() + "metadata.ini";
        QString integrationJsPath = pluginDir + QDir::separator() + "integration.js";

        Mock<IFileFactory> fileFactoryMock;
        Mock<IFile> integrationJsFileMock;
        When(Method(integrationJsFileMock, exists)).Return(true);
        When(Method(integrationJsFileMock, open)).Return(true);
        When(Method(integrationJsFileMock, path)).Return(integrationJsPath);
        Fake(Dtor(integrationJsFileMock));

        IFile& file = integrationJsFileMock.get();
        QString usedIntegrationJsPath;
        When(Method(fileFactoryMock, create)).AlwaysDo([&](auto path) {
            usedIntegrationJsPath = path;
            shared_ptr<IFile> filePtr(&file, [](IFile*){ });
            return filePtr;
        });

        QString pluginUrl = "https://service.com";
        QMap<QString, QVariant> iniData;
        iniData["author"] = "authorName";
        iniData["author_website"] = "authorUrl";
        iniData["icon"] = "logo.svg";
        iniData["name"] = "pluginName";
        iniData["version"] = "pluginVersion";
        iniData["url"] = pluginUrl;

        Mock<IIniFile> metatadaIniFileMock;
        Fake(Dtor(metatadaIniFileMock));
        When(Method(metatadaIniFileMock, path)).Return(metadataPath);
        When(Method(metatadaIniFileMock, value)).AlwaysDo([&](const QString& key) -> QVariant
                                                          {
                                                              return iniData[key];
                                                          });

        IIniFile& iniFile = metatadaIniFileMock.get();
        Mock<IIniFileFactory> iniFileFactoryMock;
        QString usedMetadataPath;
        When(Method(iniFileFactoryMock, create)).AlwaysDo([&](auto path)
                                                          {
                                                              usedMetadataPath = path;
                                                              shared_ptr<IIniFile> iniFilePtr(&iniFile, [](IIniFile*){ });
                                                              return iniFilePtr;
                                                          });

        WebPlayerPlugin plugin(pluginDir, fileFactoryMock.get(), iniFileFactoryMock.get(), settingsStore);

        WHEN("load a valid plugin") {
            QString code = "function update\n"
                           "function play\n"
                           "function pause\n"
                           "function goNext\n"
                           "function goPrevious\n"
                           "function setVolume\n"
                           "function addToFavorites\n"
                           "function removeFromFavorites\n"
                           "function seekToPosition\n";
            When(Method(integrationJsFileMock, content)).Return(code);
            plugin.load();

            THEN("fileFactory is called with integration.js path") {
                Check(Verify(Method(fileFactoryMock, create)).Once());
                REQUIRE(usedIntegrationJsPath == integrationJsPath);

                AND_THEN("a valid script is created") {
                    REQUIRE(plugin.script()->isValid());
                }
            }

            AND_THEN("iniFileFactory is called with metads") {
                Check(Verify(Method(iniFileFactoryMock, create)).Once());
                REQUIRE(usedMetadataPath == metadataPath);

                AND_THEN("metadata are not empty") {
                    REQUIRE(!plugin.metadata()->name().isEmpty());
                    REQUIRE(!plugin.metadata()->author().isEmpty());
                    REQUIRE(!plugin.metadata()->authorUrl().isEmpty());
                    REQUIRE(!plugin.metadata()->version().isEmpty());
                    REQUIRE(!plugin.metadata()->logo().isEmpty());
                    REQUIRE(plugin.url() == pluginUrl);
                }
            }
        }

        WHEN("load an invalid plugin script") {
            QString invalidCode = "invalid code";
            When(Method(integrationJsFileMock, content)).Return(invalidCode);

            THEN("throws runtime_error") {
                REQUIRE_THROWS(plugin.load());
            }
        }
    }
}
