#pragma once

#include "IContextProperties.hpp"
#include <QList>

namespace MellowPlayer::Domain
{
    class IPlayer;
}

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
        ContextProperties(IQmlApplicationEngine& qmlApplicationEngine, Domain::IPlayer& player);

        void add(IContextProperty& contextProperty) override;

        void initialize() override;

    private:
        IQmlApplicationEngine& qmlApplicationEngine_;
        QList<IContextProperty*> contextProperties_;
        Domain::IPlayer& player_;
    };
}
