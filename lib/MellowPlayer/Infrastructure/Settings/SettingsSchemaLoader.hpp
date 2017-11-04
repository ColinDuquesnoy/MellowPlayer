#pragma once

#include <MellowPlayer/Domain/Settings/ISettingsSchemaLoader.hpp>

class QJsonDocument;

namespace MellowPlayer::Infrastructure
{
    class SettingsSchemaLoader : public Domain::ISettingsSchemaLoader
    {
    public:
        QJsonDocument load() const override;
    };
}
