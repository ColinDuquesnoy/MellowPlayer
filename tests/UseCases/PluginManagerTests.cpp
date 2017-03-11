#include <catch.hpp>
#include <Mocks/PluginLoaderMock.hpp>
#include <MellowPlayer/UseCases.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;
using namespace std;

TEST_CASE("PluginManagerManagerTests") {
    auto mock = PluginLoaderMock::get();
    PluginManager pluginManager(mock.get());
    QSignalSpy pluginAddedSpy(&pluginManager, SIGNAL(pluginAdded(Entities::Plugin*)));
    pluginManager.load();

    SECTION("load called PluginLoader::load") {
        Verify(Method(mock, load)).Exactly(1);
        REQUIRE(pluginManager.getServices().count() > 1);
    };

    SECTION("pluginAdded signal is emitted for each service loaded") {
        REQUIRE(pluginAddedSpy.count() > 1);
    }

    SECTION("get with valid service name") {
        REQUIRE(pluginManager.get("Deezer").getName() == "Deezer");
    };

    SECTION("get with unknown service name throws") {
        CHECK_THROWS(pluginManager.get("Unknown"));
    }

    SECTION("current service is initially empty") {
        REQUIRE(pluginManager.getCurrentPlugin() == nullptr);
    }

    SECTION("set current service ") {
        QSignalSpy currentPluginChangedSignal(&pluginManager,
                                               SIGNAL(currentPluginChanged(Entities::Plugin*)));
        pluginManager.setCurrentPlugin(&pluginManager.get("Deezer"));
        REQUIRE(pluginManager.getCurrentPlugin() != nullptr);
        REQUIRE(currentPluginChangedSignal.count() == 1);
        pluginManager.setCurrentPlugin(&pluginManager.get("Deezer"));
        REQUIRE(currentPluginChangedSignal.count() == 1);
    }

    SECTION("reload ") {
        pluginAddedSpy.clear();
        pluginManager.load();
        REQUIRE(pluginAddedSpy.count() == 0);
    }
}
