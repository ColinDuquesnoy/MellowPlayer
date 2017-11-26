#pragma once

#include "IContextProperty.hpp"

namespace MellowPlayer::Presentation
{
    class IContextProperties;

    /**
     * All context properties should inherit from this intermediary base class in order to be added automatically
     * to the application's QML context.
     */
    class ContextProperty: public IContextProperty
    {
    public:
        /**
         * Constructor that adds the property to the qml context.
         *
         * @param contextProperties
         */
        ContextProperty(IContextProperties& contextProperties);
    };
}
