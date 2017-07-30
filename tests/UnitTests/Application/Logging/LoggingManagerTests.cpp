#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Application;

TEST_CASE("LoggingManagerTests", "[UnitTest]")
{
    SECTION("logger given no args returns root logger")
    {
        auto& logger = LoggingManager::logger();
        REQUIRE(logger.name() == "root");
    }

    SECTION("logger given same args twice return same logger instance")
    {
        auto& logger1 = LoggingManager::logger("sameLoggerTest");
        auto& logger2 = LoggingManager::logger("sameLoggerTest");
        REQUIRE(&logger1 == &logger2);
    }
}