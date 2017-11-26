#pragma once

#include <MellowPlayer/Presentation/Qml/IContextProperty.hpp>
#include <gmock/gmock.h>

namespace MellowPlayer::Presentation::Tests
{
    class ContextPropertyMock: public QObject, public IContextProperty
    {
    public:
        ContextPropertyMock()
        {
            ON_CALL(*this, asQObject()).WillByDefault(testing::Return(this));
            ON_CALL(*this, name()).WillByDefault(testing::Return("FakeContextProperty"));
        }

        MOCK_CONST_METHOD0(name, QString());
        MOCK_METHOD0(asQObject, QObject*());
    };
}
