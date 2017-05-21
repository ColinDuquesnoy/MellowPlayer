#pragma once

#include <MellowPlayer/UseCases/Settings/ISettingsSchemaLoader.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SettingsSchemaLoader: public UseCases::ISettingsSchemaLoader {
public:
    QJsonDocument load() const override;

};

END_MELLOWPLAYER_NAMESPACE
