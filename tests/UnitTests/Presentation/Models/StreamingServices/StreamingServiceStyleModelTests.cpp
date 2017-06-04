#include <catch.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServiceStyleModel.hpp>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
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
    StreamingServices& streamingServices = injector.create<StreamingServices&>();
    StreamingServiceStyleModel pluginStyleModel(streamingServices, settings);
    streamingServices.setCurrent(nullptr);

    SECTION("initially use StreamingServiceStyle::defaultStyle") {
        requireMatchStyle(pluginStyleModel, pluginStyleModel.getDefaultStyle());
    }

    SECTION("use pluginStyle when current streamingService changed") {
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        requireMatchStyle(pluginStyleModel, StreamingServiceLoaderMock::PLUGIN_STYLE);
        streamingServices.setCurrent(&streamingServices.get("Spotify"));
        requireMatchStyle(pluginStyleModel, StreamingServiceLoaderMock::PLUGIN_STYLE);
    }

    SECTION("setUsePluginTests") {
        REQUIRE(pluginStyleModel.getUsePluginStyle());
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        requireMatchStyle(pluginStyleModel, StreamingServiceLoaderMock::PLUGIN_STYLE);
        pluginStyleModel.setUsePluginStyle(false);
        REQUIRE(!pluginStyleModel.getUsePluginStyle());
        requireMatchStyle(pluginStyleModel, pluginStyleModel.getDefaultStyle());
        pluginStyleModel.setUsePluginStyle(false);
        requireMatchStyle(pluginStyleModel, pluginStyleModel.getDefaultStyle());
        pluginStyleModel.setUsePluginStyle(true);
        requireMatchStyle(pluginStyleModel, StreamingServiceLoaderMock::PLUGIN_STYLE);
    }

    SECTION("getColorScaleFactor") {
        REQUIRE(pluginStyleModel.getColorScaleFactor("black") > pluginStyleModel.getColorScaleFactor("white"));
    }
}