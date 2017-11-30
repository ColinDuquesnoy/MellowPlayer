#include <MellowPlayer/Infrastructure/Applications/DeprecatedSingleInstanceApplication.hpp>
#include <Mocks/ApplicationMock.hpp>
#include <Mocks/FakeCommnandLineArguments.hpp>
#include <Mocks/PlayerMock.hpp>
#include <QtTest/QtTest>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

TEST_CASE("SingleInstanceApplication")
{
    auto appMock1 = ApplicationMock::get();
    FakeCommandLineArguments commandLineParserMock;
    auto playerMock = PlayerMock::get();
    DeprecatedSingleInstanceApplication instance1(appMock1.get(), commandLineParserMock, playerMock.get());

    instance1.run();
    Verify(Method(appMock1, run)).Exactly(1);
    QTest::qWait(500);
    Verify(Method(appMock1, initialize)).Exactly(1);

    SECTION("Second instance should quit")
    {
        auto appMock2 = ApplicationMock::get();
        DeprecatedSingleInstanceApplication instance2(appMock2.get(), commandLineParserMock, playerMock.get());
        auto retCode = instance2.run();
        QTest::qWait(500);
        REQUIRE(retCode == 0);
    }
}
