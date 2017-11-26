#pragma once

#include <MellowPlayer/Presentation/Qml/IContextProperties.hpp>
#include <gmock/gmock.h>

namespace MellowPlayer::Presentation::Tests
{
    class ContextPropertiesMock: public IContextProperties
    {
    public:
        MOCK_METHOD1(add, void(IContextProperty&));
    };
}
