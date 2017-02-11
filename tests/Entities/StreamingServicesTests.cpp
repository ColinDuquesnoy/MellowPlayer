#include <catch.hpp>
#include <MellowPlayer/Entities.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(Entities)

TEST_CASE("StreamingService::getAuthor") {
    PluginMetadata pluginMetadata;
    pluginMetadata.author = "Colin Duquesnoy";
    StreamingService service(pluginMetadata);
    REQUIRE(service.getAuthor() == pluginMetadata.author);
}

TEST_CASE("StreamingService::getAuthorWebsite") {
    PluginMetadata pluginMetadata;
    pluginMetadata.authorWebsite = "https://gitlab.com/ColinDuquesnoy";
    StreamingService service(pluginMetadata);
    REQUIRE(service.getAuthorWebsite() == pluginMetadata.authorWebsite);
}

TEST_CASE("Plugins::getToolbarColor_validColor") {
    PluginMetadata pluginMetadata;
    pluginMetadata.color = "#ffff00";
    StreamingService service(pluginMetadata);
    REQUIRE(service.getToolbarColor() == pluginMetadata.color);
}

TEST_CASE("Plugins::getToolbarColor_invalidColor") {
    PluginMetadata pluginMetadata;
    pluginMetadata.color = "qzpodkqpodzkpqokzd";
    StreamingService service(pluginMetadata);
    QString color = service.getToolbarColor();
    REQUIRE(color == "");
}

TEST_CASE("Plugins.getName") {
    PluginMetadata pluginMetadata;
    pluginMetadata.name = "Deezer";
    StreamingService service(pluginMetadata);
    REQUIRE(service.getName() == pluginMetadata.name); // need Qt5Svg
}

TEST_CASE("Plugins.getLogo_validImage") {
    PluginMetadata pluginMetadata;
    pluginMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
    StreamingService service(pluginMetadata);
    REQUIRE(service.getLogo() == "file://" + pluginMetadata.logoPath);
}

TEST_CASE("Plugins.getLogo_nullImage") {
    PluginMetadata pluginMetadata;
    pluginMetadata.logoPath = "";
    StreamingService service(pluginMetadata);
    REQUIRE(service.getLogo().isEmpty());
}

TEST_CASE("StreamingService.getUrl") {
    PluginMetadata pluginMetadata;
    pluginMetadata.url = "https://deezer.com";
    StreamingService service(pluginMetadata);
    REQUIRE(service.getUrl() == pluginMetadata.url);

    QSignalSpy spy(&service, SIGNAL(urlChanged(QString)));
    service.setCustomUrl("https://deezer.com/news");
    REQUIRE(service.getUrl() == "https://deezer.com/news");
    REQUIRE(spy.count() == 1);
}

TEST_CASE("StreamingService.getVersion") {
    PluginMetadata pluginMetadata;
    pluginMetadata.version = "1.2";
    StreamingService service(pluginMetadata);
    REQUIRE(service.getVersion() == pluginMetadata.version);
}

TEST_CASE("StreamingService.equalityOperator") {
    PluginMetadata pluginMetadata1;
    pluginMetadata1.name = "Deezer";
    pluginMetadata1.url = "https://deezer.com";
    StreamingService plugin1(pluginMetadata1);

    PluginMetadata pluginMetadata2;
    pluginMetadata2.name = "Spotify";
    pluginMetadata2.url = "https://play.spotify.com";
    StreamingService plugin2(pluginMetadata2);

    StreamingService plugin3(pluginMetadata1);

    REQUIRE(plugin1 != plugin2);
    REQUIRE(plugin1 == plugin3);
}
