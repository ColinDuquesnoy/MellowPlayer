#include <catch.hpp>
#include <MellowPlayer/Presentation/ViewModels/StyleViewModel.hpp>
#include "DI.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

void requireMatchStyle(StyleViewModel& styleModel, const Style& style) {
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
    StreamingServicesController& streamingServices = injector.create<StreamingServicesController&>();
    IStyleLoader& styleLoader = injector.create<IStyleLoader&>();
    streamingServices.load();
    StyleViewModel styleViewModel(streamingServices, settings, styleLoader);
    streamingServices.setCurrent(nullptr);

    SECTION("initially use Style::defaultStyle") {
        requireMatchStyle(styleViewModel, styleViewModel.getCustomStyle());
    }

    SECTION("use service style when current streamingService changed and theme is set to adaptive") {
        settings.get(SettingKey::APPEARANCE_THEME).setValue("Adaptive");
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        requireMatchStyle(styleViewModel, StreamingServiceLoaderMock::DEFAULT_STYLE);
        streamingServices.setCurrent(&streamingServices.get("Spotify"));
        requireMatchStyle(styleViewModel, StreamingServiceLoaderMock::DEFAULT_STYLE);
    }

    SECTION("getColorScaleFactor") {
        REQUIRE(styleViewModel.getColorScaleFactor("black") > styleViewModel.getColorScaleFactor("white"));
    }

    SECTION("more than 3 available styles") {
        REQUIRE(styleViewModel.getAvailableStyles().count() > 3);
    }


}