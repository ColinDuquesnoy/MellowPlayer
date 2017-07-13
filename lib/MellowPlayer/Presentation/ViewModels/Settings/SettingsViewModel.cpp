#include <QtCore/QAbstractItemModel>
#include "MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp"
#include "SettingsViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


SettingsViewModel::SettingsViewModel(Settings& settings,
                                     StyleViewModel& styleViewModel,
                                     QObject* parent) :
        QObject(parent),
        settings(settings),
        settingViewModelFactory(styleViewModel),
        categories(new SettingsCategoryListModel(this, "name")) {
    for(SettingsCategory* category: settings.getCategories()) {
        if (category->getKey() != "private")
            categories->append(new SettingsCategoryViewModel(styleViewModel, category, this));
    }
    categories->append(new CustomSettingsCategoryViewModel(
            "Services", u8"\ue405", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/ServiceSettingsPage.qml", styleViewModel, this));
    categories->append(new CustomSettingsCategoryViewModel(
            "Cache", u8"\ue872", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/CacheSettingsPage.qml", styleViewModel, this));
}

SettingViewModel* SettingsViewModel::get(int key) {
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = settings.get(settingKey);
    return settingViewModelFactory.create(setting, nullptr);
}

SettingsCategoryListModel* SettingsViewModel::getCategories() const {
    return categories;
}

void SettingsViewModel::restoreDefaults() {
    settings.restoreDefaults();
}
