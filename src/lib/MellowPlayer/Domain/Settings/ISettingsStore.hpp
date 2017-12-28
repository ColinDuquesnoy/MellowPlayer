#pragma once

#include <QString>
#include <QVariant>

namespace MellowPlayer::Domain
{
    class ISettingsStore
    {
    public:
        virtual ~ISettingsStore() = default;

        virtual void clear() = 0;

        virtual QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const = 0;
        virtual void setValue(const QString& key, const QVariant& value) = 0;
    };
}