#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceWatcher.hpp>
#include <QtTest/QSignalSpy>
#include <QtTest/qtestsystem.h>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include "Utils/Helpers.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;


TEST_CASE("StreamingServiceWatcherTests") {
    StreamingServiceCreator creator;
    auto pluginDir = creator.create("TestService", "https://test-service.com", "MellowPlayer.Tests", "https://travis-ci.org/MellowPlayer");
    REQUIRE(QDir(pluginDir).exists());

    StreamingServiceMetadata metadata;
    metadata.pluginDirectory = pluginDir;
    metadata.scriptPath = pluginDir + "/" + "integration.js";

    REQUIRE(QDir().exists(metadata.scriptPath));
    StreamingService service(metadata);
    StreamingServiceWatcher watcher;
    watcher.watch(service);

    QSignalSpy scriptChangedSpy(&service, &StreamingService::scriptChanged);
    QSignalSpy themeChangedSpy(&service, &StreamingService::themeChanged);

    REQUIRE(scriptChangedSpy.count() == 0);
    REQUIRE(themeChangedSpy.count() == 0);

    QTest::qWait(1000);

    SECTION("change script file content") {
        REQUIRE(writeFile(pluginDir + "/" + "integration.js", "test"));
        QTest::qWait(1000);
        REQUIRE(scriptChangedSpy.count() == 1);
    }

    SECTION("change theme file content") {
        REQUIRE(writeFile(pluginDir + "/" + "theme.json", "test"));
        QTest::qWait(1000);
        REQUIRE(themeChangedSpy.count() == 1);
    }

    QDir().rmpath(pluginDir);
}
