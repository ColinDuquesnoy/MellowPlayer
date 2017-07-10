#pragma once

#include "MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp"

namespace MellowPlayer::Application {

    class Setting;

}

namespace MellowPlayer::Presentation {

    class SettingViewModelFactory {
    public:
        SettingViewModel* create(Application::Setting& setting, QObject* parent=nullptr) const;
    };

}
