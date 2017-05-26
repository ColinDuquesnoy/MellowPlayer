#include <catch.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServiceStyleModel.hpp>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

void requireMatchStyle(StreamingServiceStyleModel& styleModel, const StreamingServiceStyle& style) {
    if (styleModel.isDark(styleModel.getBackground()))
        REQUIRE(styleModel.getTheme() == "dark");
    else
        REQUIRE(styleModel.getTheme() == "light");
    REQUIRE(styleModel.getAccent() == style.accent);
    REQUIRE(styleModel.getBackground() == style.background);
    REQUIRE(styleModel.getForeground() == style.foreground);
    REQUIRE(styleModel.getPrimary() == style.primary);
    REQUIRE(styleModel.getPrimaryForeground() == style.primaryForeground);
    REQUIRE(styleModel.getSecondary() == style.secondary);
    REQUIRE(styleModel.getSecondaryForeground() == style.secondaryForeground);
}

TEST_CASE("StyleViewModelTests", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    StreamingServicePluginService& pluginService = injector.create<StreamingServicePluginService&>();
    StreamingServiceStyleModel pluginStyleModel(pluginService, settings);
    pluginService.setCurrent(nullptr);

    SECTION("initially use StreamingServiceStyle::defaultStyle") {
        requireMatchStyle(pluginStyleModel, pluginStyleModel.getDefaultStyle());
    }

    SECTION("use pluginStyle when current plugin changed") {
        pluginService.setCurrent(&pluginService.get("Deezer"));
        requireMatchStyle(pluginStyleModel, PluginLoaderMock::PLUGIN_STYLE);
        pluginService.setCurrent(&pluginService.get("Spotify"));
        requireMatchStyle(pluginStyleModel, PluginLoaderMock::PLUGIN_STYLE);
    }

    SECTION("setUsePluginTests") {
        REQUIRE(pluginStyleModel.getUsePluginStyle());
        pluginService.setCurrent(&pluginService.get("Deezer"));
        requireMatchStyle(pluginStyleModel, PluginLoaderMock::PLUGIN_STYLE);
        pluginStyleModel.setUsePluginStyle(false);
        REQUIRE(!pluginStyleModel.getUsePluginStyle());
        requireMatchStyle(pluginStyleModel, pluginStyleModel.getDefaultStyle());
        pluginStyleModel.setUsePluginStyle(false);
        requireMatchStyle(pluginStyleModel, pluginStyleModel.getDefaultStyle());
        pluginStyleModel.setUsePluginStyle(true);
        requireMatchStyle(pluginStyleModel, PluginLoaderMock::PLUGIN_STYLE);
    }

    SECTION("getColorScaleFactor") {
        REQUIRE(pluginStyleModel.getColorScaleFactor("black") > pluginStyleModel.getColorScaleFactor("white"));
    }
}