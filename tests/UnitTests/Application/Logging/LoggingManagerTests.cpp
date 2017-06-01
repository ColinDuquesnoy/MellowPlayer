#include <catch.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)

TEST_CASE("LoggingManagerTests", "[UnitTest]") {
    SECTION("getLogger given no args returns root logger") {
        auto& logger = LoggingManager::instance().getLogger();
        REQUIRE(logger.getName() == "root");
    }

    SECTION("getLogger given same args twice return same logger instance") {
        auto& logger1 = LoggingManager::instance().getLogger("sameLoggerTest");
        auto& logger2 = LoggingManager::instance().getLogger("sameLoggerTest");
        REQUIRE(&logger1 == &logger2);
    }
}