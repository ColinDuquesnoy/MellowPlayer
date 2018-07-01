#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <UnitTests/Domain/Settings/FakeSettingsStore.hpp>
#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>
#include <Lib/Utils/DependencyPool.hpp>

using namespace MellowPlayer::Tests;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("StreamingServiceLoaderTests")
{
    DependencyPool pool;
    auto loader = StreamingServiceLoader(pool.getSettings());

    SECTION("load")
    {
        auto services = loader.load();
        REQUIRE(services.count() > 1);
    }
}
