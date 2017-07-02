#pragma once

#include "MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, Setting)
BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingViewModelFactory {
public:
    SettingViewModel* create(Application::Setting& setting, QObject* parent=nullptr) const;
};

END_MELLOWPLAYER_NAMESPACE
