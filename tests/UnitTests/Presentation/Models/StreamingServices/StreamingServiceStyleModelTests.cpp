#include <catch.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServiceStyleModel.hpp>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

void requireMatchStyle(StreamingServiceStyleModel& styleViewModel, const StreamingServiceStyle& style) {
    REQUIRE(styleViewModel.getTheme() == style.theme);
    REQUIRE(styleViewModel.getAccent() == style.accent);
    REQUIRE(styleViewModel.getBackground() == style.background);
    REQUIRE(styleViewModel.getForeground() == style.foreground);
    REQUIRE(styleViewModel.getPrimary() == style.primary);
    REQUIRE(styleViewModel.getPrimaryForeground() == style.primaryForeground);
    REQUIRE(styleViewModel.getSecondary() == style.secondary);
    REQUIRE(styleViewModel.getSecondaryForeground() == style.secondaryForeground);
}

TEST_CASE("StyleViewModelTests", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    StreamingServicePluginService& pluginService = injector.create<StreamingServicePluginService&>();
    StreamingServiceStyleModel pluginStyleModel(pluginService);
    pluginService.setCurrent(nullptr);

    SECTION("initially use StreamingServiceStyle::defaultStyle") {
        requireMatchStyle(pluginStyleModel, StreamingServiceStyle::defaultStyle());
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
        requireMatchStyle(pluginStyleModel, StreamingServiceStyle::defaultStyle());
        pluginStyleModel.setUsePluginStyle(false);
        requireMatchStyle(pluginStyleModel, StreamingServiceStyle::defaultStyle());
        pluginStyleModel.setUsePluginStyle(true);
        requireMatchStyle(pluginStyleModel, PluginLoaderMock::PLUGIN_STYLE);
    }

    SECTION("getColorScaleFactor") {
        REQUIRE(pluginStyleModel.getColorScaleFactor("black") > pluginStyleModel.getColorScaleFactor("white"));
    }
}