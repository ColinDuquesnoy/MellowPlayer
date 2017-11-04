#pragma once

#include "SettingsCategoryViewModel.hpp"
#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/Models/SettingsCategoryListModel.hpp>

namespace MellowPlayer::Domain
{
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class SettingViewModel;
    class ThemeViewModel;

    class SettingsViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractItemModel* categories READ categories CONSTANT)
    public:
        SettingsViewModel(Domain::Settings& settings, ThemeViewModel& themeViewModel, QObject* parent = nullptr);

        Q_INVOKABLE SettingViewModel* get(int key);
        SettingsCategoryListModel* categories() const;
        Q_INVOKABLE void restoreDefaults();

    private:
        Domain::Settings& settings_;
        SettingViewModelFactory factory_;
        SettingsCategoryListModel* categories_;
    };
}
