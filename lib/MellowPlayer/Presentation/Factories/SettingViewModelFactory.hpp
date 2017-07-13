#pragma once

#include "MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp"

namespace MellowPlayer::Application {

    class Setting;

}

namespace MellowPlayer::Presentation {

    class StyleViewModel;

    class SettingViewModelFactory {
    public:
        SettingViewModelFactory(StyleViewModel& styleViewModel);
        SettingViewModel* create(Application::Setting& setting, QObject* parent=nullptr) const;

    private:
        StyleViewModel& styleViewModel;
    };

}
