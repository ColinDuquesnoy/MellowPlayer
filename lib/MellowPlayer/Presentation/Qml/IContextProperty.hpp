#pragma once

#include <QString>

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
         * Name of the context property.
         */
        virtual QString name() const = 0;

        /**
         * Gets the QObject context property.
         */
        virtual QObject* asQObject() = 0;
    };
}
