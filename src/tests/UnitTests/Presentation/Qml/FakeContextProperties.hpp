#pragma once

#include <MellowPlayer/Presentation/Qml/IContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/IContextProperty.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeContextProperties: public IContextProperties
    {
    public:
        void setQmlApplicationEngine(IQmlApplicationEngine* qmlApplicationEngine)
        {
            qmlApplicationEngine_ = qmlApplicationEngine;
        }

        void add(IContextProperty& contextProperty) override
        {
            _items.append(&contextProperty);
        }

        bool contains(IContextProperty& contextProperty)
        {
            return _items.contains(&contextProperty);
        }

        void initialize() override
        {
            if (qmlApplicationEngine_)
            {
                for(auto* contextProperty: _items)
                    if (contextProperty)
                        contextProperty->initialize(*qmlApplicationEngine_);
            }
        }

    private:
        QList<IContextProperty*> _items;
        IQmlApplicationEngine* qmlApplicationEngine_ = nullptr;
    };

}
