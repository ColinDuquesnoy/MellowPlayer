#include <catch.hpp>
#include <MellowPlayer/Entities.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(Entities)

TEST_CASE("Plugin::getAuthor") {
    PluginMetadata pluginMetadata;
    pluginMetadata.author = "Colin Duquesnoy";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getAuthor() == pluginMetadata.author);
}

TEST_CASE("Plugin::getAuthorWebsite") {
    PluginMetadata pluginMetadata;
    pluginMetadata.authorWebsite = "https://gitlab.com/ColinDuquesnoy";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getAuthorWebsite() == pluginMetadata.authorWebsite);
}

TEST_CASE("Plugins::getToolbarColor_validColor") {
    PluginMetadata pluginMetadata;
    pluginMetadata.color = "#ffff00";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getToolbarColor() == pluginMetadata.color);
}

TEST_CASE("Plugins::getToolbarColor_invalidColor") {
    PluginMetadata pluginMetadata;
    pluginMetadata.color = "qzpodkqpodzkpqokzd";
    Plugin plugin(pluginMetadata);
    QString color = plugin.getToolbarColor();
    REQUIRE(color == "");
}

TEST_CASE("Plugins.getName") {
    PluginMetadata pluginMetadata;
    pluginMetadata.name = "Deezer";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getName() == pluginMetadata.name); // need Qt5Svg
}

TEST_CASE("Plugins.getLogo_validImage") {
    PluginMetadata pluginMetadata;
    pluginMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getLogo() == "file://" + pluginMetadata.logoPath);
}

TEST_CASE("Plugins.getLogo_nullImage") {
    PluginMetadata pluginMetadata;
    pluginMetadata.logoPath = "";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getLogo().isEmpty());
}

TEST_CASE("Plugin.getUrl") {
    PluginMetadata pluginMetadata;
    pluginMetadata.url = "https://deezer.com";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getUrl() == pluginMetadata.url);

    QSignalSpy spy(&plugin, SIGNAL(urlChanged(QString)));
    plugin.setCustomUrl("https://deezer.com/news");
    REQUIRE(plugin.getUrl() == "https://deezer.com/news");
    REQUIRE(spy.count() == 1);
}

TEST_CASE("Plugin.getScript") {
    PluginMetadata pluginMetadata;
    pluginMetadata.script = "code";
    pluginMetadata.scriptPath = "path";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getScript().getCode() == "code");
    REQUIRE(plugin.getScript().getPath() == "path");
}

TEST_CASE("Plugin.getScriptPtr") {
    PluginMetadata pluginMetadata;
    pluginMetadata.script = "code";
    pluginMetadata.scriptPath = "path";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getScriptPtr()->getCode() == "code");
    REQUIRE(plugin.getScriptPtr()->getPath() == "path");
}

TEST_CASE("Plugin.getVersion") {
    PluginMetadata pluginMetadata;
    pluginMetadata.version = "1.2";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getVersion() == pluginMetadata.version);
}

TEST_CASE("Plugin.equalityOperator") {
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