#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include "FakeQmlApplicationEngine.hpp"
#include "FakeContextProperties.hpp"
#include <catch/catch.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("ContextPropertyTests")
{
    GIVEN("A fake qml application engine and list of context properties")
    {
        FakeQmlApplicationEngine qmlApplicationEngine;
        QObject propertyObject;
        FakeContextProperties contextProperties;
        contextProperties.setQmlApplicationEngine(&qmlApplicationEngine);

        WHEN("I create a context property")
        {
            ContextProperty contextProperty("ContextPropertyName", &propertyObject, contextProperties);

            THEN("propertyObject has been added to the context properties")
            {
                REQUIRE(contextProperties.contains(contextProperty));
            }

            AND_WHEN("I call initialize on contextProperties")
            {
                contextProperties.initialize();

                THEN("context property was added to the qmlApplicationEngine")
                {
                    REQUIRE(qmlApplicationEngine.contextProperty("ContextPropertyName") == &propertyObject);
                }
            }

        }
    }
}
