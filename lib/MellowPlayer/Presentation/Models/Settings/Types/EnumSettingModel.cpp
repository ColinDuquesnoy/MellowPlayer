#include "EnumSettingModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

EnumSettingModel::EnumSettingModel(Setting& setting, QObject* parent) : SettingModel(setting, parent) {

}

QString EnumSettingModel::getValue() const {
    return setting.getValue().toString();
}

void EnumSettingModel::setValue(QString value) {
    setting.setValue(value);
}

void EnumSettingModel::onValueChanged() {
    emit valueChanged();
}

QString EnumSettingModel::getQmlComponent() {
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/EnumSettingDelegate.qml";
}

QStringList EnumSettingModel::getValues() const {
    QString list = setting.getType();
    list = list.replace("enum[", "").replace("]", "").replace("'", "").trimmed();
    return list.split(",");
}
