#pragma once

#include <MellowPlayer/Presentation/Qml/IContextProperties.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeContextProperties: public IContextProperties
    {
    public:
        void add(IContextProperty& contextProperty) override
        {
            _items.append(&contextProperty);
        }

        bool contains(IContextProperty& contextProperty)
        {
            return _items.contains(&contextProperty);
        }

    private:
        QList<IContextProperty*> _items;
    };
}
