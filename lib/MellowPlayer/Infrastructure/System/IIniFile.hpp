#pragma once

#include <QtCore/QVariant>

namespace MellowPlayer::Infrastructure
{
    class IIniFile
    {
    public:
        virtual ~IIniFile() = default;

        virtual QString path() const = 0;
        virtual QVariant value(const QString& key) const = 0;
        virtual QVariant value(const QString& key, const QVariant& defaultValue) const = 0;
    };
}
