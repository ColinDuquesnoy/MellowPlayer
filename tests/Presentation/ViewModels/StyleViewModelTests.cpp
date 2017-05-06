#include <catch.hpp>
#include <MellowPlayer/Presentation/ViewModels/StyleViewModel.hpp>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

void requireMatchStyle(StyleViewModel& styleViewModel, const PluginStyle& style) {
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
    PluginService& pluginService = injector.create<PluginService&>();
    StyleViewModel styleViewModel(pluginService);
    pluginService.setCurrent(nullptr);

    SECTION("initially use PluginStyle::defaultStyle") {
        requireMatchStyle(styleViewModel, PluginStyle::defaultStyle());
    }

    SECTION("use pluginStyle when current plugin changed") {
        pluginService.setCurrent(&pluginService.get("Deezer"));
        requireMatchStyle(styleViewModel, PluginLoaderMock::PLUGIN_STYLE);
        pluginService.setCurrent(&pluginService.get("Spotify"));
        requireMatchStyle(styleViewModel, PluginLoaderMock::PLUGIN_STYLE);
    }

    SECTION("setUsePluginTests") {
        REQUIRE(styleViewModel.getUsePluginStyle());
        pluginService.setCurrent(&pluginService.get("Deezer"));
        requireMatchStyle(styleViewModel, PluginLoaderMock::PLUGIN_STYLE);
        styleViewModel.setUsePluginStyle(false);
        REQUIRE(!styleViewModel.getUsePluginStyle());
        requireMatchStyle(styleViewModel, PluginStyle::defaultStyle());
        styleViewModel.setUsePluginStyle(false);
        requireMatchStyle(styleViewModel, PluginStyle::defaultStyle());
        styleViewModel.setUsePluginStyle(true);
        requireMatchStyle(styleViewModel, PluginLoaderMock::PLUGIN_STYLE);
    }

    SECTION("getColorScaleFactor") {
        REQUIRE(styleViewModel.getColorScaleFactor("black") > styleViewModel.getColorScaleFactor("white"));
    }
}