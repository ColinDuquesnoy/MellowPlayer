#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

void requireMatchTheme(ThemeViewModel& themeViewModel, const Theme& theme)
{
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

TEST_CASE("ThemeViewModelTests", "[UnitTest]")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    StreamingServicesController& streamingServices = pool.getStreamingServicesController();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();

    streamingServices.load();
    settings.get(SettingKey::APPEARANCE_THEME).setValue("Adaptive");
    streamingServices.setCurrent(nullptr);

    SECTION("initially use default theme")
    {
        requireMatchTheme(themeViewModel, themeViewModel.getTheme("Default"));
    }

    SECTION("use service theme when current streamingService changed and theme "
            "is set to adaptive")
    {
        settings.get(SettingKey::APPEARANCE_THEME).setValue("Adaptive");
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        requireMatchTheme(themeViewModel, StreamingServiceLoaderMock::DEFAULT_theme);
        streamingServices.setCurrent(&streamingServices.get("Spotify"));
        requireMatchTheme(themeViewModel, StreamingServiceLoaderMock::DEFAULT_theme);
    }

    SECTION("getColorScaleFactor")
    {
        REQUIRE(themeViewModel.getColorScaleFactor("black") > themeViewModel.getColorScaleFactor("white"));
    }

    SECTION("isDark")
    {
        REQUIRE(!themeViewModel.isDark("white"));
        REQUIRE(themeViewModel.isDark("black"));
        REQUIRE(themeViewModel.isDark("#ffc107"));
        REQUIRE(themeViewModel.isDark("#4fa6d3"));
        REQUIRE(!themeViewModel.isDark("#00ffff"));
    }

    SECTION("more than 3 available theme")
    {
        REQUIRE(themeViewModel.getAvailableThemes().count() > 3);
    }
}
