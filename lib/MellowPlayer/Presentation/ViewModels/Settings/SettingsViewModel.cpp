#include <QtCore/QAbstractItemModel>
#include "MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp"
#include "SettingsViewModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)


SettingsViewModel::SettingsViewModel(Settings& settings, QObject* parent) : QObject(parent), settings(settings), categories(
        new SettingsCategoryListModel(this, "name")) {
    for(SettingsCategory* category: settings.getCategories()) {
        if (category->getKey() != "private")
            categories->append(new SettingsCategoryViewModel(category, this));
    }
    categories->append(new CustomSettingsCategoryViewModel(
            "Services", u8"\ue405", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/ServiceSettingsPage.qml", this));
    categories->append(new CustomSettingsCategoryViewModel(
            "Cache", u8"\ue872", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/CacheSettingsPage.qml", this));
}

SettingViewModel* SettingsViewModel::get(int key) {
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = settings.get(settingKey);
    return settingModelFactory.create(setting, nullptr);
}

SettingsCategoryListModel* SettingsViewModel::getCategories() const {
    return categories;
}

void SettingsViewModel::restoreDefaults() {
    settings.restoreDefaults();
}
