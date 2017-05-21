#include <catch.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include <MellowPlayer/Entities/PluginScript.hpp>
#include <QtTest/QSignalSpy>
#include <Mocks/SettingsProviderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)

TEST_CASE("PluginTest", "[UnitTest]") {
    PluginMetadata pluginMetadata;

    SECTION("Plugin::getAuthor") {
        pluginMetadata.author = "Colin Duquesnoy";
        Plugin service(pluginMetadata);
        REQUIRE(service.getAuthor() == pluginMetadata.author);
    }

    SECTION("Plugin::getAuthorWebsite") {
        pluginMetadata.authorWebsite = "https://gitlab.com/ColinDuquesnoy";
        Plugin service(pluginMetadata);
        REQUIRE(service.getAuthorWebsite() == pluginMetadata.authorWebsite);
    }

    SECTION("Plugins::getColor_validColor") {
        pluginMetadata.color = "#ffff00";
        Plugin service(pluginMetadata);
        REQUIRE(service.getColor() == pluginMetadata.color);
    }

    SECTION("Plugins::getToolbarColor_invalidColor") {
        pluginMetadata.color = "qzpodkqpodzkpqokzd";
        Plugin service(pluginMetadata);
        QString color = service.getColor();
        REQUIRE(color == "");
    }

    SECTION("Plugins.getName") {
        pluginMetadata.name = "Deezer";
        Plugin service(pluginMetadata);
        REQUIRE(service.getName() == pluginMetadata.name);
    }

    SECTION("Plugins.getLogo_validImage") {
        pluginMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
        Plugin service(pluginMetadata);
        REQUIRE(service.getLogo() == "file://" + pluginMetadata.logoPath);
    }

    SECTION("Plugins.getLogo_nullImage") {
        pluginMetadata.logoPath = "";
        Plugin service(pluginMetadata);
        REQUIRE(service.getLogo().isEmpty());
    }

    SECTION("Plugin.getUrl") {
        pluginMetadata.url = "https://deezer.com";
        Plugin service(pluginMetadata);
        REQUIRE(service.getUrl() == pluginMetadata.url);
    }

    SECTION("Plugin.getScript") {
        pluginMetadata.script = "code";
        pluginMetadata.scriptPath = "path";
        Plugin service(pluginMetadata);
        auto script = service.getScript();
        REQUIRE(script->getCode() == "code");
        REQUIRE(script->getPath() == "path");
    }

    SECTION("Plugin.getVersion") {
        pluginMetadata.version = "1.2";
        Plugin service(pluginMetadata);
        REQUIRE(service.getVersion() == pluginMetadata.version);
    }

    SECTION("Plugin.equalityOperator") {
        PluginMetadata pluginMetadata1;
        pluginMetadata1.name = "Deezer";
        pluginMetadata1.url = "https://deezer.com";
        Plugin plugin1(pluginMetadata1);

        PluginMetadata pluginMetadata2;
        pluginMetadata2.name = "Spotify";
        pluginMetadata2.url = "https://play.spotify.com";
        Plugin plugin2(pluginMetadata2);

        Plugin plugin3(pluginMetadata1);

        REQUIRE(plugin1 != plugin2);
        REQUIRE(plugin1 == plugin3);
    }
}

