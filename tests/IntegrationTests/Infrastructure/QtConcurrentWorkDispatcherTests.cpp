#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <QtTest/qtestsystem.h>
#include <catch.hpp>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("QtConcurrentWorkDispatcherTests")
{
    QtConcurrentWorkDispatcher workDispatcher;

    SECTION("invoke")
    {
        bool finished = false;
        workDispatcher.invoke([&]() { finished = true; });
        REQUIRE(!finished);
        sleep_for(milliseconds(100));
        REQUIRE(finished);
    }

    SECTION("delayInvoke")
    {
        bool finished = false;
        workDispatcher.delayInvoke(100, [&]() { finished = true; });
        REQUIRE(!finished);
        QTest::qWait(1000);
        REQUIRE(finished);
    }
}
