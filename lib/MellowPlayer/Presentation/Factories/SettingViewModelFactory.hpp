#pragma once

#include "MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp"

namespace MellowPlayer::Application
{
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class ThemeViewModel;

    class SettingViewModelFactory
    {
    public:
        SettingViewModelFactory(ThemeViewModel &themeViewModel);
        SettingViewModel *create(Application::Setting &setting, QObject *parent = nullptr) const;

    private:
        ThemeViewModel &themeViewModel;
    };
}
