#pragma once

#include <MellowPlayer/Application/Settings/ISettingsSchemaLoader.hpp>

class QJsonDocument;

namespace MellowPlayer::Infrastructure
{
    class SettingsSchemaLoader : public Application::ISettingsSchemaLoader
    {
    public:
        QJsonDocument load() const override;
    };
}
