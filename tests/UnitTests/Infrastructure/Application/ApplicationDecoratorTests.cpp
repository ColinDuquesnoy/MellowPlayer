#include <MellowPlayer/Infrastructure/Application/ApplicationDecorator.hpp>
#include <catch/catch.hpp>
#include <QtTest/QSignalSpy>
#include "FakeApplication.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("ApplicationDecoratorTests")
{
    GIVEN("An application mock")
    {
        auto decorated = make_shared<FakeApplication>();
        ApplicationDecorator decorator(decorated);

        WHEN("decorated started signal is emitted")
        {
            QSignalSpy spy(&decorator, &IApplication::started);

            emit decorated->started();

            THEN("decorator started signal is emitted too")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("decorated initialized signal is emitted")
        {
            QSignalSpy spy(&decorator, &IApplication::initialized);

            emit decorated->initialized();

            THEN("decorator initialized signal is emitted too")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("decorated restoreWindowRequest signal is emitted")
        {
            QSignalSpy spy(&decorator, &IApplication::restoreWindowRequest);

            emit decorated->restoreWindowRequest();

            THEN("decorator restoreWindowRequest signal is emitted too")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("decorated commitDataRequest signal is emitted")
        {
            QSignalSpy spy(&decorator, &IApplication::commitDataRequest);

            emit decorated->commitDataRequest();

            THEN("decorator commitDataRequest signal is emitted too")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("decorator initialize is called")
        {
            decorator.initialize();

            THEN("decorated is initialized")
            {
                REQUIRE(decorated->isInitialized);
            }
        }

        WHEN("decorator run is called")
        {
            decorated->returnCode = 42;
            auto retCode = decorator.run();

            THEN("decorated is running")
            {
                REQUIRE(decorated->isRunning);
            }

            AND_THEN("return value of decorated is returned")
            {
                REQUIRE(retCode == 42);
            }
        }

        WHEN("decorator quit is called")
        {
            decorator.quit();

            THEN("quit was requested on the decorated")
            {
                REQUIRE(decorated->quitRequested);
            }
        }

        WHEN("decorator restart is called")
        {
            decorator.restart();

            THEN("restart was requested on the decorated")
            {
                REQUIRE(decorated->restartRequested);
            }
        }

        WHEN("decorator restoreWindow is called")
        {
            decorator.restoreWindow();

            THEN("restoreWindow was requested on the decorated")
            {
                REQUIRE(decorated->restoreWindowRequested);
            }
        }
    }
}
