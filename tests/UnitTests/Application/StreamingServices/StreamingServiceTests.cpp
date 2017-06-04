#include <catch.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServiceScript.hpp>
#include <QtTest/QSignalSpy>
#include <Mocks/SettingsProviderMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)

TEST_CASE("StreamingServiceTest", "[UnitTest]") {
    StreamingServiceMetadata pluginMetadata;

    SECTION("StreamingService::getAuthor") {
        pluginMetadata.author = "Colin Duquesnoy";
        StreamingService service(pluginMetadata);
        REQUIRE(service.getAuthor() == pluginMetadata.author);
    }

    SECTION("StreamingService::getAuthorWebsite") {
        pluginMetadata.authorWebsite = "https://gitlab.com/ColinDuquesnoy";
        StreamingService service(pluginMetadata);
        REQUIRE(service.getAuthorWebsite() == pluginMetadata.authorWebsite);
    }

    SECTION("Plugins::getColor_validColor") {
        pluginMetadata.color = "#ffff00";
        StreamingService service(pluginMetadata);
        REQUIRE(service.getColor() == pluginMetadata.color);
    }

    SECTION("Plugins::getToolbarColor_invalidColor") {
        pluginMetadata.color = "qzpodkqpodzkpqokzd";
        StreamingService service(pluginMetadata);
        QString color = service.getColor();
        REQUIRE(color == "");
    }

    SECTION("Plugins.getName") {
        pluginMetadata.name = "Deezer";
        StreamingService service(pluginMetadata);
        REQUIRE(service.getName() == pluginMetadata.name);
    }

    SECTION("Plugins.getLogo_validImage") {
        pluginMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
        StreamingService service(pluginMetadata);
        REQUIRE(service.getLogo() == "file://" + pluginMetadata.logoPath);
    }

    SECTION("Plugins.getLogo_nullImage") {
        pluginMetadata.logoPath = "";
        StreamingService service(pluginMetadata);
        REQUIRE(service.getLogo().isEmpty());
    }

    SECTION("StreamingService.getUrl") {
        pluginMetadata.url = "https://deezer.com";
        StreamingService service(pluginMetadata);
        REQUIRE(service.getUrl() == pluginMetadata.url);
    }

    SECTION("StreamingService.getScript") {
        pluginMetadata.script = "code";
        pluginMetadata.scriptPath = "path";
        StreamingService service(pluginMetadata);
        auto script = service.getScript();
        REQUIRE(script->getCode() == "code");
        REQUIRE(script->getPath() == "path");
    }

    SECTION("StreamingService.getVersion") {
        pluginMetadata.version = "1.2";
        StreamingService service(pluginMetadata);
        REQUIRE(service.getVersion() == pluginMetadata.version);
    }

    SECTION("StreamingService.equalityOperator") {
        StreamingServiceMetadata pluginMetadata1;
        pluginMetadata1.name = "Deezer";
        pluginMetadata1.url = "https://deezer.com";
        StreamingService service0(pluginMetadata1);

        StreamingServiceMetadata pluginMetadata2;
        pluginMetadata2.name = "Spotify";
        pluginMetadata2.url = "https://play.spotify.com";
        StreamingService service1(pluginMetadata2);

        StreamingService service2(pluginMetadata1);

        REQUIRE(service0 != service1);
        REQUIRE(service0 == service2);
    }
}

