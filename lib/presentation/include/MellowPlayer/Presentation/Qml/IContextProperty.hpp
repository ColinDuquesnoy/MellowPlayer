#pragma once

#include <QString>
#include "IQmlApplicationEngine.hpp"

class QObject;

namespace MellowPlayer::Presentation
{
    class IQmlApplicationEngine;

    /**
     * Represents a qml context property. If added to IContextProperties, it will be automatically registered in
     * the qml context as a named context property.
     */
    class IContextProperty
    {
    public:
        virtual ~IContextProperty() = default;

        /**
         * Initialize the context property
         *
         * @param qmlApplicationEngine
         */
        virtual void initialize(IQmlApplicationEngine& qmlApplicationEngine) = 0;
    };
}
