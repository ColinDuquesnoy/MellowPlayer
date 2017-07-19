#include <chrono>
#include <thread>
#include <catch.hpp>
#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>

using namespace std::this_thread;
using namespace std::chrono;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("QtConcurrentWorkDispatcherTests") {
    QtConcurrentWorkDispatcher workDispatcher;
    bool finished = false;
    workDispatcher.invoke([&](){
        sleep_for(milliseconds(100));
        finished = true;
    });
    REQUIRE(!finished);
    sleep_for(milliseconds(200));
    REQUIRE(finished);
}
