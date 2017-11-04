#include <MellowPlayer/Infrastructure/Applications/SingleInstanceApplication.hpp>
#include <Mocks/ApplicationMock.hpp>
#include <Mocks/CommnandLineParserMock.hpp>
#include <Mocks/PlayerMock.hpp>
#include <QtTest/QtTest>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("SingleInstanceApplication")
{
    auto appMock1 = ApplicationMock::get();
    auto commandLineParserMock = CommandLineParserMock::get();
    auto playerMock = PlayerMock::get();
    SingleInstanceApplication instance1(appMock1.get(), commandLineParserMock.get(), playerMock.get());

    instance1.run();
    Verify(Method(appMock1, run)).Exactly(1);
    QTest::qWait(500);
    Verify(Method(appMock1, initialize)).Exactly(1);

    SECTION("Second instance should quit")
    {
        auto appMock2 = ApplicationMock::get();
        SingleInstanceApplication instance2(appMock2.get(), commandLineParserMock.get(), playerMock.get());
        auto retCode = instance2.run();
        QTest::qWait(500);
        REQUIRE(retCode == 0);
    }
}
