#include <MellowPlayer/Infrastructure/Application/ApplicationDecorator.hpp>
#include <catch.hpp>
#include <QtTest/QSignalSpy>
#include "ApplicationMock.hpp"

using namespace testing;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("ApplicationDecoratorTests")
{
    GIVEN("An application mock")
    {
        ApplicationMock decorated;
        ApplicationDecorator decorator(decorated);

        WHEN("decorated started signal is emitted")
        {
            QSignalSpy spy(&decorator, &IApplication::started);

            emit decorated.started();

            THEN("decorator started signal is emitted too")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("decorated initialized signal is emitted")
        {
            QSignalSpy spy(&decorator, &IApplication::initialized);

            emit decorated.initialized();

            THEN("decorator initialized signal is emitted too")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("decorated restoreWindowRequest signal is emitted")
        {
            QSignalSpy spy(&decorator, &IApplication::restoreWindowRequest);

            emit decorated.restoreWindowRequest();

            THEN("decorator restoreWindowRequest signal is emitted too")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("decorated commitDataRequest signal is emitted")
        {
            QSignalSpy spy(&decorator, &IApplication::commitDataRequest);

            emit decorated.commitDataRequest();

            THEN("decorator commitDataRequest signal is emitted too")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("decorator initialize is called")
        {
            THEN("decorated initialize is called too")
            {
                EXPECT_CALL(decorated, initialize()).Times(1);
            }

            decorator.initialize();
        }

        WHEN("decorator run is called")
        {
            ON_CALL(decorated, run()).WillByDefault(Return(42));

            THEN("decorated run is called too")
            {
                EXPECT_CALL(decorated, run()).Times(1);
            }

            auto retCode = decorator.run();

            AND_THEN("return value of decorated is returned")
            {
                REQUIRE(retCode == 42);
            }
        }

        WHEN("decorator quit is called")
        {
            THEN("decorated quit is called too")
            {
                EXPECT_CALL(decorated, quit()).Times(1);
            }

            decorator.quit();
        }

        WHEN("decorator restart is called")
        {
            THEN("decorated restart is called too")
            {
                EXPECT_CALL(decorated, restart()).Times(1);
            }

            decorator.restart();
        }

        WHEN("decorator restoreWindow is called")
        {
            THEN("decorated restoreWindow is called too")
            {
                EXPECT_CALL(decorated, restoreWindow()).Times(1);
            }

            decorator.restoreWindow();
        }
    }
}
