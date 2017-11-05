#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <Mocks/SettingsStoreMock.hpp>
#include <catch.hpp>
#include <fakeit.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("StreamingServiceLoaderTests")
{
    StreamingServiceLoader loader;

    SECTION("load")
    {
        auto services = loader.load();
        REQUIRE(services.count() > 1);
    }
}
