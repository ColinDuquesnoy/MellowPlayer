#include <catch.hpp>
#include <Mocks/PluginLoaderMock.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include <MellowPlayer/UseCases/Services/PluginService.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;
using namespace std;

TEST_CASE("PluginServiceTests") {
    auto mock = PluginLoaderMock::get();
    PluginService pluginService(mock.get());
    QSignalSpy pluginAddedSpy(&pluginService, SIGNAL(pluginAdded(Entities::Plugin*)));
    pluginService.load();

    SECTION("load called PluginLoader::load") {
        Verify(Method(mock, load)).Exactly(1);
        REQUIRE(pluginService.getAll().count() > 1);
    };

    SECTION("pluginAdded signal is emitted for each service loaded") {
        REQUIRE(pluginAddedSpy.count() > 1);
    }

    SECTION("get with valid service name") {
        REQUIRE(pluginService.get("Deezer").getName() == "Deezer");
    };

    SECTION("get with unknown service name throws") {
        CHECK_THROWS(pluginService.get("Unknown"));
    }

    SECTION("current service is initially empty") {
        REQUIRE(pluginService.getCurrent() == nullptr);
    }

    SECTION("set current service ") {
        QSignalSpy currentPluginChangedSignal(&pluginService,
                                               SIGNAL(currentPluginChanged(Entities::Plugin*)));
        pluginService.setCurrent(&pluginService.get("Deezer"));
        REQUIRE(pluginService.getCurrent() != nullptr);
        REQUIRE(currentPluginChangedSignal.count() == 1);
        pluginService.setCurrent(&pluginService.get("Deezer"));
        REQUIRE(currentPluginChangedSignal.count() == 1);
    }

    SECTION("reload ") {
        pluginAddedSpy.clear();
        pluginService.load();
        REQUIRE(pluginAddedSpy.count() == 0);
    }
}
