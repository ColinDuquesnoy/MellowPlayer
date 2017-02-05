#include <catch.hpp>
#include <MellowPlayer/Logging.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)

TEST_CASE("LoggingManager.getLogger_noArgs") {
    auto& logger = LoggingManager::instance().getLogger();
    REQUIRE(logger.getName() == "root");
}

TEST_CASE("LoggingManager.getLogger_twiceIsSame") {
    auto& logger1 = LoggingManager::instance().getLogger("sameLoggerTest");
    auto& logger2 = LoggingManager::instance().getLogger("sameLoggerTest");
    REQUIRE(&logger1 == &logger2);
}