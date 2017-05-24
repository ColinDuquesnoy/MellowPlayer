#include "SettingsCategoryModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)


SettingsCategoryModel::SettingsCategoryModel(SettingsCategory* settingsCategory, QObject* parent) :
        QObject(parent), settingsCategory(settingsCategory),
        settingsListModel(new QQmlObjectListModel<SettingModel>(this, "name")) {
    if (settingsCategory != nullptr)
        for(Setting* setting: settingsCategory->getSettings())
            settingsListModel->append(settingModelFactory.create(*setting, this));
}

QString SettingsCategoryModel::getName() const {
    return settingsCategory != nullptr ? settingsCategory->getName() : "";
}

QString SettingsCategoryModel::getIcon() const {
    return settingsCategory != nullptr ? settingsCategory->getIcon() : "";
}

QString SettingsCategoryModel::getQmlComponent() const {
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/AutomaticSettingsPage.qml";
}

QAbstractItemModel* SettingsCategoryModel::getSettingsModel() {
    return settingsListModel;
}

CustomSettingsCategoryModel::CustomSettingsCategoryModel(const QString& name, const QString& icon,
                                                         const QString& qmlComponent, QObject* parent):
    SettingsCategoryModel(nullptr, parent), name(name), icon(icon), qmlComponent(qmlComponent) {

}

QString CustomSettingsCategoryModel::getName() const {
    return name;
}

QString CustomSettingsCategoryModel::getIcon() const {
    return icon;
}

QString CustomSettingsCategoryModel::getQmlComponent() const {
    return qmlComponent;
}
