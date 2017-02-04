#include <catch.hpp>
#include <MellowPlayer/Entities.hpp>

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
    REQUIRE(plugin.getName() == pluginMetadata.name);
}

TEST_CASE("Plugins.getLogo_validImage") {
    PluginMetadata pluginMetadata;
    pluginMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
    Plugin plugin(pluginMetadata);
    REQUIRE(!plugin.getLogo().isNull());
}

TEST_CASE("Plugins.getLogo_nullImage") {
    PluginMetadata pluginMetadata;
    pluginMetadata.logoPath = "";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getLogo().isNull());
}

TEST_CASE("Plugin.getUrl") {
    PluginMetadata pluginMetadata;
    pluginMetadata.url = "https://deezer.com";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getUrl() == pluginMetadata.url);

    plugin.setCustomUrl("https://deezer.com/news");
    REQUIRE(plugin.getUrl() == "https://deezer.com/news");
}

TEST_CASE("Plugin.getVersion") {
    PluginMetadata pluginMetadata;
    pluginMetadata.version = "1.2";
    Plugin plugin(pluginMetadata);
    REQUIRE(plugin.getVersion() == pluginMetadata.version);
}
