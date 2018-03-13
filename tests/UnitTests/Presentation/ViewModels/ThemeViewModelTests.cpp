#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <UnitTests/Domain/StreamingServices/FakeStreamingServiceLoader.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

void requireMatchTheme(ThemeViewModel& themeViewModel, const Theme& theme)
{
    if (themeViewModel.isDark(themeViewModel.background()))
        REQUIRE(themeViewModel.isDark());
    else
        REQUIRE(!themeViewModel.isDark());
    REQUIRE(themeViewModel.accent() == theme.accent);
    REQUIRE(themeViewModel.background().toStdString() == theme.background.toStdString());
    REQUIRE(themeViewModel.foreground() == theme.foreground);
    REQUIRE(themeViewModel.primary() == theme.primary);
    REQUIRE(themeViewModel.primaryForeground() == theme.primaryForeground);
    REQUIRE(themeViewModel.secondary() == theme.secondary);
    REQUIRE(themeViewModel.secondaryForeground() == theme.secondaryForeground);
}

TEST_CASE("ThemeViewModelTests", "[UnitTest]")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    StreamingServices& streamingServices = pool.getStreamingServices();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();

    streamingServices.load();
    settings.get(SettingKey::APPEARANCE_THEME).setValue("Adaptive");
    streamingServices.setCurrent(nullptr);

    SECTION("initially use default theme")
    {
        requireMatchTheme(themeViewModel, themeViewModel.theme("Default"));
    }

    SECTION("use service theme when current streamingService changed and theme "
            "is set to adaptive")
    {
        settings.get(SettingKey::APPEARANCE_THEME).setValue("Adaptive");
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        requireMatchTheme(themeViewModel, FakeStreamingServiceLoader::defaultTheme());
        streamingServices.setCurrent(&streamingServices.get("Spotify"));
        requireMatchTheme(themeViewModel, FakeStreamingServiceLoader::defaultTheme());
    }

    SECTION("colorScaleFactor")
    {
        REQUIRE(themeViewModel.colorScaleFactor("black") > themeViewModel.colorScaleFactor("white"));
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
        REQUIRE(themeViewModel.availableThemes().count() > 3);
    }
}
