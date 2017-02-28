#include <QtCore>
#ifdef Q_OS_LINUX
#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Applications/LinuxApplication.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/MprisServiceMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("LinuxApplicationTests") {
    auto mainWindowMock = MainWindowMock::get();
    auto hotkeysMock = HotkeysServiceMock::get();
    auto qtAppMock = QtApplicationMock::get();
    auto mprisMock = MprisServiceMock::get();
    LinuxApplication app(qtAppMock.get(), mainWindowMock.get(), hotkeysMock.get(), mprisMock.get());

    SECTION("initialize") {
        app.initialize();
        Verify(Method(hotkeysMock, start)).Exactly(1);
        Verify(Method(mainWindowMock, load)).Exactly(1);
        Verify(Method(mprisMock, start)).Exactly(1);
    }
}
#endif
