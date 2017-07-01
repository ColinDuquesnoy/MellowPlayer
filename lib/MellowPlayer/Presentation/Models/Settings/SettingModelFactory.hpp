#pragma once

#include "Types/SettingModel.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, Setting)
BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingModelFactory {
public:
    SettingModel* create(Application::Setting& setting, QObject* parent=nullptr) const;
};

END_MELLOWPLAYER_NAMESPACE
