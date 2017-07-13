#pragma once

#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/Models/SettingsCategoryListModel.hpp>
#include "SettingsCategoryViewModel.hpp"

namespace MellowPlayer::Presentation {

    class SettingsViewModel: public QObject {
        Q_OBJECT
        Q_PROPERTY(QAbstractItemModel* categories READ getCategories CONSTANT)
    public:
        SettingsViewModel(Application::Settings& settings, StyleViewModel& styleViewModel,
                          QObject* parent= nullptr);

        Q_INVOKABLE SettingViewModel* get(int key);
        SettingsCategoryListModel* getCategories() const;
        Q_INVOKABLE void restoreDefaults();

    private:
        Application::Settings& settings;
        SettingViewModelFactory settingViewModelFactory;
        SettingsCategoryListModel* categories;
    };

}
