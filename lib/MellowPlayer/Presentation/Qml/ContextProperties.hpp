#pragma once

#include "IContextProperties.hpp"

namespace MellowPlayer::Presentation
{
    class IQmlApplicationEngine;

    /**
     * Implements IContextProperties interface
     */
    class ContextProperties: public IContextProperties
    {
    public:
        /**
         * Ctor
         * @param qmlApplicationEngine Qml application engine used to set context properties.
         */
        ContextProperties(IQmlApplicationEngine& qmlApplicationEngine);

        void add(IContextProperty& contextProperty) override;

    private:
        IQmlApplicationEngine& qmlApplicationEngine_;
    };
}
