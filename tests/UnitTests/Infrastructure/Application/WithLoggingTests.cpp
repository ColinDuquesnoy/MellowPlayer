#include <MellowPlayer/Infrastructure/Application/WithLogging.hpp>
#include <Mocks/CommnandLineArgumentsMock.hpp>
#include <Lib/TestMacros.hpp>
#include "ApplicationMock.hpp"
#include <UnitTests/Domain/Logging/LoggerFactoryMock.hpp>
#include <memory>

using namespace std;
using namespace testing;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("WithLoggingTests")
{
    GIVEN("An application with logging")
    {
        NiceMock<ApplicationMock> application;
        NiceMock<CommandLineArgumentsMock> commandLineArguments;
        unique_ptr<ILoggerFactory> loggerFactory = make_unique<NiceMock<LoggerFactoryMock>>();

        WithLogging appWithLogging(application, loggerFactory, commandLineArguments);

        WHEN("initialize is called")
        {
            THEN("decorated application is initialized too")
            {
                EXPECT_CALL(application, initialize()).Times(1);
            }

            appWithLogging.initialize();
        }
    }
}
