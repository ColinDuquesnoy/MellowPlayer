#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Plugins/PluginMetadata.hpp>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <fakeit/fakeit.hpp>

using namespace fakeit;
using namespace std;
using namespace MellowPlayer::Infrastructure;

SCENARIO("PluginMetadataTests")
{
    GIVEN("a PluginMetadata")
    {
        QString iniFilePath = "/path/to/plugin/metadata.ini";

        WHEN("loading metadata using fake data")
        {
            QMap<QString, QVariant> iniData;
            iniData["author"] = "authorName";
            iniData["author_website"] = "authorUrl";
            iniData["icon"] = "logo.svg";
            iniData["name"] = "pluginName";
            iniData["version"] = "pluginVersion";

            Mock<IIniFile> iniFileMock;
            Fake(Dtor(iniFileMock));
            When(Method(iniFileMock, path)).Return(iniFilePath);
            When(Method(iniFileMock, value)).AlwaysDo([&](const QString& key) -> QVariant {
                return iniData[key];
            });
            IIniFile& iniFile = iniFileMock.get();
            shared_ptr<IIniFile> iniFilePtr;
            iniFilePtr.reset(&iniFile);
            PluginMetadata pluginMetadata(iniFilePtr);

            pluginMetadata.load();

            AND_THEN("values are correctly set")
            {
                REQUIRE(pluginMetadata.author() == "authorName");
                REQUIRE(pluginMetadata.authorUrl() == "authorUrl");
                REQUIRE(pluginMetadata.name() == "pluginName");
                REQUIRE(pluginMetadata.version() == "pluginVersion");
                REQUIRE(pluginMetadata.logo() == QFileInfo(QFileInfo(iniFilePath).dir(), "logo.svg").absoluteFilePath());
            }
        }
    }
}