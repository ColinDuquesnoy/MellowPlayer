#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include "QmlApplicationEngineMock.hpp"
#include "ContextPropertyMock.hpp"
#include <catch.hpp>

using namespace testing;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("ContextPropertiesTests")
{
    GIVEN("A context properties instance with a fake qml application engine")
    {
        QmlApplicationEngineMock qmlApplicationEngine;
        ContextProperties contextProperties(qmlApplicationEngine);

        WHEN("adding a context property")
        {
            ContextPropertyMock contextProperty;

            THEN("call IContextProperty::name()")
            {
                EXPECT_CALL(contextProperty, name()).Times(1);
            }

            AND_THEN("call IContextProperty::asQObject()")
            {
                EXPECT_CALL(contextProperty, asQObject()).Times(1);
            }

            AND_THEN("call IQmlApplicationEngine::setContextProperty")
            {
                EXPECT_CALL(qmlApplicationEngine, setContextProperty(
                        contextProperty.name(), contextProperty.asQObject())).Times(1);
            }

            contextProperties.add(contextProperty);
        }
    }
}
