#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilterFactory.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/IPlatformFilter.hpp>
#include <QtCore/QList>

using namespace MellowPlayer::Infrastructure;

SCENARIO("PlatformFilterFactoryTests")
{
    GIVEN("a PlatformFilterFactory instance")
    {
        PlatformFilterFactory factory;

        WHEN("creating a valid filter")
        {
            QList<Filter> filters = {
                    Filter::All,
                    Filter::Linux,
                    Filter::Windows,
                    Filter::AppImage,
                    Filter::OSX
            };

            for(auto filter: filters) {
                THEN(QString("filter is not nullptr (%1)").arg(static_cast<int>(filter)).toStdString())
                {
                    REQUIRE(factory.create(filter) != nullptr);
                }
            }
        }
    }
}
