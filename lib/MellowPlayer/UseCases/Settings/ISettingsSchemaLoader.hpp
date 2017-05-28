#pragma once

#include <QJsonDocument>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ISettingsSchemaLoader {
public:
    virtual ~ISettingsSchemaLoader() = default;

    virtual QJsonDocument load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
