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
    StreamingServiceStyleModel streamingServiceStyleModel(streamingServices, settings);
    streamingServices.setCurrent(nullptr);

    SECTION("initially use StreamingServiceStyle::defaultStyle") {
        requireMatchStyle(streamingServiceStyleModel, streamingServiceStyleModel.getDefaultStyle());
    }

    SECTION("useServiceStyle when current streamingService changed") {
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        requireMatchStyle(streamingServiceStyleModel, StreamingServiceLoaderMock::DEFAULT_STYLE);
        streamingServices.setCurrent(&streamingServices.get("Spotify"));
        requireMatchStyle(streamingServiceStyleModel, StreamingServiceLoaderMock::DEFAULT_STYLE);
    }

    SECTION("setUseServiceStyle") {
        REQUIRE(streamingServiceStyleModel.getUseServiceStyle());
        streamingServices.setCurrent(&streamingServices.get("Deezer"));
        requireMatchStyle(streamingServiceStyleModel, StreamingServiceLoaderMock::DEFAULT_STYLE);
        streamingServiceStyleModel.setUseServiceStyle(false);
        REQUIRE(!streamingServiceStyleModel.getUseServiceStyle());
        requireMatchStyle(streamingServiceStyleModel, streamingServiceStyleModel.getDefaultStyle());
        streamingServiceStyleModel.setUseServiceStyle(false);
        requireMatchStyle(streamingServiceStyleModel, streamingServiceStyleModel.getDefaultStyle());
        streamingServiceStyleModel.setUseServiceStyle(true);
        requireMatchStyle(streamingServiceStyleModel, StreamingServiceLoaderMock::DEFAULT_STYLE);
    }

    SECTION("getColorScaleFactor") {
        REQUIRE(streamingServiceStyleModel.getColorScaleFactor("black") > streamingServiceStyleModel.getColorScaleFactor("white"));
    }
}