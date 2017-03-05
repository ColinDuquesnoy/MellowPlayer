#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Infrastructure/StreamingServicesLoader.hpp>
#include <Mocks/ApplicationSettingsMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

TEST_CASE("StreamingServicesLoader load plugins from CMAKE_SOURCE_DIR", "[StreamingServicesLoader][Infrastructure][IntegrationTest]") {
    auto appSettingsMock = ApplicationSettingsMock::get();
    StreamingServicesLoader pluginLoader(appSettingsMock.get());
    StreamingServicesList plugins = pluginLoader.load();
    REQUIRE(plugins.count() > 1);
}

