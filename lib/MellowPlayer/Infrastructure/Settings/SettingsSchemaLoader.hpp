#pragma once

#include <MellowPlayer/Application/Settings/ISettingsSchemaLoader.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SettingsSchemaLoader: public Application::ISettingsSchemaLoader {
public:
    QJsonDocument load() const override;

};

END_MELLOWPLAYER_NAMESPACE
