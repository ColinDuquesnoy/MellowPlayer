#include <QtCore/QAbstractItemModel>
#include "MellowPlayer/Presentation/Models/Settings/Types/SettingModel.hpp"
#include "SettingsModel.hpp"
#include "QQmlObjectListModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)


SettingsModel::SettingsModel(Settings& settings, QObject* parent) : QObject(parent), settings(settings), categories(
        new QQmlObjectListModel<SettingsCategoryModel>(this, "name")) {
    for(SettingsCategory* category: settings.getCategories()) {
        if (category->getKey() != "private")
            categories->append(new SettingsCategoryModel(category, this));
    }
    categories->append(new CustomSettingsCategoryModel(
            "Services", u8"\ue405", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/ServiceSettingsPage.qml", this));
    categories->append(new CustomSettingsCategoryModel(
            "Cache", u8"\ue872", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/CacheSettingsPage.qml", this));
}

SettingModel* SettingsModel::get(int key) {
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = settings.get(settingKey);
    return settingModelFactory.create(setting, nullptr);
}

QAbstractItemModel* SettingsModel::getCategories() const {
    return categories;
}

void SettingsModel::restoreDefaults() {
    settings.restoreDefaults();
}
