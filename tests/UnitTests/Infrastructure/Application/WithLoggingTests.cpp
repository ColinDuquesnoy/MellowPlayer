#include <MellowPlayer/Infrastructure/Application/WithLogging.hpp>
#include <Mocks/FakeCommnandLineArguments.hpp>
#include <Lib/TestMacros.hpp>
#include "FakeApplication.hpp"
#include <UnitTests/Domain/Logging/FakeLoggerFactory.hpp>
#include <memory>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("WithLoggingTests")
{
    GIVEN("An application with logging")
    {
        auto decorated = make_shared<FakeApplication>();
        FakeCommandLineArguments commandLineArguments;
        WithLogging appWithLogging(decorated, commandLineArguments);

        WHEN("initialize is called")
        {
            appWithLogging.initialize();

            THEN("decorated is initialized too")
            {
                REQUIRE(decorated->isInitialized);
            }
        }
    }
}
