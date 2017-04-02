#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Applications/SingleInstanceApplication.hpp>
#include <Mocks/ApplicationMock.hpp>
#include <QtTest/QtTest>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("SingleInstanceApplication", "[IntegrationTest]") {
    auto appMock1 = ApplicationMock::get();
    SingleInstanceApplication instance1(appMock1.get());

    instance1.run();
    Verify(Method(appMock1, run)).Exactly(1);
    QTest::qWait(100);
    Verify(Method(appMock1, initialize)).Exactly(1);

    SECTION("Second instance should quit") {
        auto appMock2 = ApplicationMock::get();
        SingleInstanceApplication instance2(appMock2.get());
        instance2.run();
        QTest::qWait(300);
        Verify(Method(appMock2, quit)).Exactly(1);
    }
}