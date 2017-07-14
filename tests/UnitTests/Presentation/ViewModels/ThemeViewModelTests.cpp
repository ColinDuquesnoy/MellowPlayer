#include <catch.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include "DI.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

void requireMatchTheme(ThemeViewModel& themeViewModel, const Theme& theme) {
    if (themeViewModel.isDark(themeViewModel.getBackground()))
        REQUIRE(themeViewModel.isDark());
    else
        REQUIRE(!themeViewModel.isDark());
    REQUIRE(themeViewModel.getAccent() == theme.accent);
    REQUIRE(themeViewModel.getBackground().toStdString() == theme.background.toStdString());
    REQUIRE(themeViewModel.getForeground() == theme.foreground);
    REQUIRE(themeViewModel.getPrimary() == theme.primary);
    REQUIRE(themeViewModel.getPrimaryForeground() == theme.primaryForeground);
    REQUIRE(themeViewModel.getSecondary() == theme.secondary);
    REQUIRE(themeViewModel.getSecondaryForeground() == theme.secondaryForeground);
}

TEST_CASE("ThemeViewModelTests", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    StreamingServicesController& streamingServices = injector.create<StreamingServicesController&>();
    IThemeLoader& themeLoader = injector.create<IThemeLoader&>();
    streamingServices.load();
    settings.get(SettingKey::APPEARANCE_THEME).setValue("Adaptive");
    ThemeViewModel themeViewModel(streamingServices, settings, themeLoader);
    streamingServices.setCurrent(nullptr);

    SECTION("initially use default theme") {
        requireMatchTheme(themeViewModel, themeViewModel.getTheme("Default"));
    }

    SECTION("use service theme when current streamingService changed and theme is set to adaptive") {
        settings.get(SettingKey::APPEARANCE_THEME).setValue("Adaptive");
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        requireMatchTheme(themeViewModel, StreamingServiceLoaderMock::DEFAULT_theme);
        streamingServices.setCurrent(&streamingServices.get("Spotify"));
        requireMatchTheme(themeViewModel, StreamingServiceLoaderMock::DEFAULT_theme);
    }

    SECTION("getColorScaleFactor") {
        REQUIRE(themeViewModel.getColorScaleFactor("black") > themeViewModel.getColorScaleFactor("white"));
    }

    SECTION("more than 3 available theme") {
        REQUIRE(themeViewModel.getAvailableThemes().count() > 3);
    }


}