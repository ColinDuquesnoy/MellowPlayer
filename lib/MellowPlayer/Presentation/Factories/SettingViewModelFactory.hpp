#pragma once

class QObject;

namespace MellowPlayer::Application
{
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class ThemeViewModel;
    class SettingViewModel;

    class SettingViewModelFactory
    {
    public:
        explicit SettingViewModelFactory(ThemeViewModel& themeViewModel);
        SettingViewModel* create(Application::Setting& setting, QObject* parent = nullptr) const;

    private:
        ThemeViewModel& themeViewModel_;
    };
}
