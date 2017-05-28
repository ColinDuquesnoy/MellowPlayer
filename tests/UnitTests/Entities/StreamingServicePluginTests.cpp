#include <catch.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePluginScript.hpp>
#include <QtTest/QSignalSpy>
#include <Mocks/SettingsProviderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)

TEST_CASE("PluginTest", "[UnitTest]") {
    StreamingServicePluginMetadata pluginMetadata;

    SECTION("StreamingServicePlugin::getAuthor") {
        pluginMetadata.author = "Colin Duquesnoy";
        StreamingServicePlugin service(pluginMetadata);
        REQUIRE(service.getAuthor() == pluginMetadata.author);
    }

    SECTION("StreamingServicePlugin::getAuthorWebsite") {
        pluginMetadata.authorWebsite = "https://gitlab.com/ColinDuquesnoy";
        StreamingServicePlugin service(pluginMetadata);
        REQUIRE(service.getAuthorWebsite() == pluginMetadata.authorWebsite);
    }

    SECTION("Plugins::getColor_validColor") {
        pluginMetadata.color = "#ffff00";
        StreamingServicePlugin service(pluginMetadata);
        REQUIRE(service.getColor() == pluginMetadata.color);
    }

    SECTION("Plugins::getToolbarColor_invalidColor") {
        pluginMetadata.color = "qzpodkqpodzkpqokzd";
        StreamingServicePlugin service(pluginMetadata);
        QString color = service.getColor();
        REQUIRE(color == "");
    }

    SECTION("Plugins.getName") {
        pluginMetadata.name = "Deezer";
        StreamingServicePlugin service(pluginMetadata);
        REQUIRE(service.getName() == pluginMetadata.name);
    }

    SECTION("Plugins.getLogo_validImage") {
        pluginMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
        StreamingServicePlugin service(pluginMetadata);
        REQUIRE(service.getLogo() == "file://" + pluginMetadata.logoPath);
    }

    SECTION("Plugins.getLogo_nullImage") {
        pluginMetadata.logoPath = "";
        StreamingServicePlugin service(pluginMetadata);
        REQUIRE(service.getLogo().isEmpty());
    }

    SECTION("StreamingServicePlugin.getUrl") {
        pluginMetadata.url = "https://deezer.com";
        StreamingServicePlugin service(pluginMetadata);
        REQUIRE(service.getUrl() == pluginMetadata.url);
    }

    SECTION("StreamingServicePlugin.getScript") {
        pluginMetadata.script = "code";
        pluginMetadata.scriptPath = "path";
        StreamingServicePlugin service(pluginMetadata);
        auto script = service.getScript();
        REQUIRE(script->getCode() == "code");
        REQUIRE(script->getPath() == "path");
    }

    SECTION("StreamingServicePlugin.getVersion") {
        pluginMetadata.version = "1.2";
        StreamingServicePlugin service(pluginMetadata);
        REQUIRE(service.getVersion() == pluginMetadata.version);
    }

    SECTION("StreamingServicePlugin.equalityOperator") {
        StreamingServicePluginMetadata pluginMetadata1;
        pluginMetadata1.name = "Deezer";
        pluginMetadata1.url = "https://deezer.com";
        StreamingServicePlugin plugin1(pluginMetadata1);

        StreamingServicePluginMetadata pluginMetadata2;
        pluginMetadata2.name = "Spotify";
        pluginMetadata2.url = "https://play.spotify.com";
        StreamingServicePlugin plugin2(pluginMetadata2);

        StreamingServicePlugin plugin3(pluginMetadata1);

        REQUIRE(plugin1 != plugin2);
        REQUIRE(plugin1 == plugin3);
    }
}

