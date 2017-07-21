#pragma once

#include <QString>
#include <QVariant>

namespace MellowPlayer::Application
{
    class ISettingsProvider
    {
    public:
        virtual ~ISettingsProvider() = default;

        virtual void clear() = 0;

        virtual QVariant getValue(const QString &key, const QVariant &defaultValue = QVariant()) const = 0;
        virtual void setValue(const QString &key, const QVariant &value) = 0;
    };
}