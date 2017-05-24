#pragma once

#include "Types/SettingModel.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Setting)
BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingModelFactory {
public:
    SettingModel* create(UseCases::Setting& setting, QObject* parent) const;
};

END_MELLOWPLAYER_NAMESPACE
