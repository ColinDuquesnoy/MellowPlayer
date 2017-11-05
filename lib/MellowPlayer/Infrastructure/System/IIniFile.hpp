#pragma once

#include <QtCore/QVariant>

namespace MellowPlayer::Infrastructure
{
    class IIniFile
    {
    public:
        virtual ~IIniFile() = default;

        virtual QVariant value(const QString& key, const QVariant& defaultValue=QVariant()) const = 0;
    };
}
