#pragma once

#include <QJsonDocument>

namespace MellowPlayer::Application
{
    class ISettingsSchemaLoader
    {
    public:
        virtual ~ISettingsSchemaLoader() = default;

        virtual QJsonDocument load() const = 0;
    };
}
