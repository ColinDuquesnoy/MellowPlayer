#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Applications/SingleInstanceApplication.hpp>
#include <Mocks/ApplicationMock.hpp>
#include <QtTest/QtTest>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("SingleInstanceApplication") {
    auto appMock1 = ApplicationMock::get();
    SingleInstanceApplication instance1(appMock1.get());

    instance1.run();
    Verify(Method(appMock1, run)).Exactly(1);
    QTest::qWait(500);
    Verify(Method(appMock1, initialize)).Exactly(1);

    SECTION("Second instance should quit") {
        auto appMock2 = ApplicationMock::get();
        SingleInstanceApplication instance2(appMock2.get());
        instance2.run();
        QTest::qWait(500);
        Verify(Method(appMock2, quit)).Exactly(1);
    }
}
