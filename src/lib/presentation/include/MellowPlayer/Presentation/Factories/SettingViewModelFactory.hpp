#pragma once

class QObject;

namespace MellowPlayer::Domain
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
        SettingViewModel* create(Domain::Setting& setting, QObject* parent = nullptr) const;

    private:
        ThemeViewModel& themeViewModel_;
    };
}
