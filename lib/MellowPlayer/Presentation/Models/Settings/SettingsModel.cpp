#include <QtCore/QAbstractItemModel>
#include "MellowPlayer/Presentation/Models/Settings/Types/SettingModel.hpp"
#include "SettingsModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)


SettingsModel::SettingsModel(Settings& settings, QObject* parent) : QObject(parent), settings(settings), categories(
        new QQmlObjectListModel<SettingsCategoryModel>(this, "name")) {
    for(SettingsCategory* category: settings.getCategories()) {
        if (category->getKey() != "private")
            categories->append(new SettingsCategoryModel(category, this));
    }

    categories->append(new CustomSettingsCategoryModel(
            "Plugins", "\ue87b", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/PluginSettingsPage.qml", this));
    categories->append(new CustomSettingsCategoryModel(
            "Cache", "\ue872", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/CacheSettingsPage.qml", this));
}

SettingModel* SettingsModel::get(int key) {
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = settings.get(settingKey);
    return settingModelFactory.create(setting, this);
}

QAbstractItemModel* SettingsModel::getCategories() const {
    return categories;
}

void SettingsModel::restoreDefaults() {
    settings.restoreDefaults();
}
