#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;

TEST_CASE("LoggingManagerTests", "[UnitTest]")
{
    SECTION("logger given no args returns root logger")
    {
        auto& logger = Loggers::logger();
        REQUIRE(logger.name() == "root");
    }

    SECTION("logger given same args twice return same logger instance")
    {
        auto& logger1 = Loggers::logger("sameLoggerTest");
        auto& logger2 = Loggers::logger("sameLoggerTest");
        REQUIRE(&logger1 == &logger2);
    }
}
