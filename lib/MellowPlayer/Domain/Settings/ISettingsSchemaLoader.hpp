#pragma once

class QJsonDocument;

namespace MellowPlayer::Domain
{
    class ISettingsSchemaLoader
    {
    public:
        virtual ~ISettingsSchemaLoader() = default;

        virtual QJsonDocument load() const = 0;
    };
}
