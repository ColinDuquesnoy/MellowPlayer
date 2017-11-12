#pragma once

#include <QObject>
#include <MellowPlayer/Domain/Properties.hpp>

namespace MellowPlayer::Domain
{
    class PluginMetadata;
    class IPluginVisitor;

    class IPlugin: public QObject
    {
        Q_OBJECT
        WRITABLE_PROPERTY(bool, isEnabled, setEnabled)
        CONSTANT_OBJECT_PROPERTY(PluginMetadata, metadata)
        CONSTANT_PROPERTY(QString, path)
    public:
        virtual void load() = 0;
        virtual void accept(IPluginVisitor& visitor) = 0;
    };
}