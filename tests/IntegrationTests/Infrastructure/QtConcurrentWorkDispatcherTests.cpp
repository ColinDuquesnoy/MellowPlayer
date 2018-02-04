#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <QtTest/qtestsystem.h>
#include <catch/catch.hpp>
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
        sleep_for(milliseconds(500));
        REQUIRE(finished);
    }

    SECTION("delayInvoke")
    {
        bool finished = false;
        workDispatcher.delayInvoke(100, [&]() { finished = true; });
        QTest::qWait(1000);
        REQUIRE(finished);
    }
}
