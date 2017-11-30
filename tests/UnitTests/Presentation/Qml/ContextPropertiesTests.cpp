#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include "FakeQmlApplicationEngine.hpp"
#include "FakeContextProperty.hpp"
#include <catch.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("ContextPropertiesTests")
{
    GIVEN("A context properties instance with a fake qml application engine")
    {
        FakeQmlApplicationEngine qmlApplicationEngine;
        ContextProperties contextProperties(qmlApplicationEngine);

        WHEN("adding a context property")
        {
            FakeContextProperty contextProperty;

            contextProperties.add(contextProperty);

            THEN("property name exists")
            {
                REQUIRE(qmlApplicationEngine.hasContextProperty(contextProperty.name()));
            }

            THEN("the correct property has been added")
            {
                REQUIRE(qmlApplicationEngine.contextProperty(contextProperty.name()) == &contextProperty);
            }
        }
    }
}
