#pragma once

#include <MellowPlayer/Presentation/Qml/IContextProperty.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeContextProperty: public QObject, public IContextProperty
    {
    public:
        using QObject::QObject;

        QString name() const override
        {
            return "FakeContextProperty";
        }

        QObject* asQObject() override
        {
            return this;
        }
    };
}
