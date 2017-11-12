#pragma once

#include <QObject>
#include <MellowPlayer/Domain/Properties.hpp>

namespace MellowPlayer::Domain
{
    class PluginMetadata: public QObject
    {
        Q_OBJECT
        CONSTANT_PROPERTY(QString, author)
        CONSTANT_PROPERTY(QString, authorUrl)
        CONSTANT_PROPERTY(QString, logo)
        CONSTANT_PROPERTY(QString, name)
        CONSTANT_PROPERTY(QString, version)
    public:
        PluginMetadata();
        
        virtual void load() = 0;
    };
}
