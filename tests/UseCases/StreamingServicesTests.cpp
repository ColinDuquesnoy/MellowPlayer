#include <catch.hpp>
#include <MellowPlayer/Entities.hpp>
#include <MellowPlayer/UseCases.hpp>
#include <MellowPlayer/Infrastructure.hpp>
#include <QtTest/QSignalSpy>
#include <Mocks/ApplicationSettingsMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("StreamingServiceTest") {
    PluginMetadata pluginMetadata;
    auto appSettingsMock = ApplicationSettingsMock::get();

    SECTION("StreamingService::getAuthor") {
        pluginMetadata.author = "Colin Duquesnoy";
        StreamingService service(pluginMetadata, appSettingsMock.get());
        REQUIRE(service.getAuthor() == pluginMetadata.author);
    }

    SECTION("StreamingService::getAuthorWebsite") {
        pluginMetadata.authorWebsite = "https://gitlab.com/ColinDuquesnoy";
        StreamingService service(pluginMetadata, appSettingsMock.get());
        REQUIRE(service.getAuthorWebsite() == pluginMetadata.authorWebsite);
    }

    SECTION("Plugins::getToolbarColor_validColor") {
        pluginMetadata.color = "#ffff00";
        StreamingService service(pluginMetadata, appSettingsMock.get());
        REQUIRE(service.getToolbarColor() == pluginMetadata.color);
    }

    SECTION("Plugins::getToolbarColor_invalidColor") {
        pluginMetadata.color = "qzpodkqpodzkpqokzd";
        StreamingService service(pluginMetadata, appSettingsMock.get());
        QString color = service.getToolbarColor();
        REQUIRE(color == "");
    }

    SECTION("Plugins.getName") {
        pluginMetadata.name = "Deezer";
        StreamingService service(pluginMetadata, appSettingsMock.get());
        REQUIRE(service.getName() == pluginMetadata.name);
    }

    SECTION("Plugins.getLogo_validImage") {
        pluginMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
        StreamingService service(pluginMetadata, appSettingsMock.get());
        REQUIRE(service.getLogo() == "file://" + pluginMetadata.logoPath);
    }

    SECTION("Plugins.getLogo_nullImage") {
        pluginMetadata.logoPath = "";
        StreamingService service(pluginMetadata, appSettingsMock.get());
        REQUIRE(service.getLogo().isEmpty());
    }

    SECTION("StreamingService.getUrl") {
        ApplicationSettings realAppSettings;
        pluginMetadata.url = "https://deezer.com";
        StreamingService service(pluginMetadata, realAppSettings);
        REQUIRE(service.getUrl() == pluginMetadata.url);

        QSignalSpy spy(&service, SIGNAL(urlChanged(QString)));
        service.setCustomUrl("https://deezer.com/news");
        REQUIRE(service.getUrl() == "https://deezer.com/news");
        REQUIRE(spy.count() == 1);
    }

    SECTION("StreamingService.getScript") {
        pluginMetadata.script = "code";
        pluginMetadata.scriptPath = "path";
        StreamingService service(pluginMetadata, appSettingsMock.get());
        auto script = service.getScript();
        REQUIRE(script->getCode() == "code");
        REQUIRE(script->getPath() == "path");
    }

    SECTION("StreamingService.getVersion") {
        pluginMetadata.version = "1.2";
        StreamingService service(pluginMetadata, appSettingsMock.get());
        REQUIRE(service.getVersion() == pluginMetadata.version);
    }

    SECTION("StreamingService.equalityOperator") {
        PluginMetadata pluginMetadata1;
        pluginMetadata1.name = "Deezer";
        pluginMetadata1.url = "https://deezer.com";
        StreamingService plugin1(pluginMetadata1, appSettingsMock.get());

        PluginMetadata pluginMetadata2;
        pluginMetadata2.name = "Spotify";
        pluginMetadata2.url = "https://play.spotify.com";
        StreamingService plugin2(pluginMetadata2, appSettingsMock.get());

        StreamingService plugin3(pluginMetadata1, appSettingsMock.get());

        REQUIRE(plugin1 != plugin2);
        REQUIRE(plugin1 == plugin3);
    }
}

