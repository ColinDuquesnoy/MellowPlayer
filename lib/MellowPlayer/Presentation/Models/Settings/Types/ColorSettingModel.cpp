#include "ColorSettingModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Application)

ColorSettingModel::ColorSettingModel(Setting& setting, QObject* parent) : SettingModel(setting, parent) {

}

QColor ColorSettingModel::getValue() const {
    return QColor(setting.getValue().toString());
}

void ColorSettingModel::setValue(QColor value) {
    setting.setValue(value.name());
}

void ColorSettingModel::onValueChanged() {
    emit valueChanged();
}

QString ColorSettingModel::getQmlComponent() {
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/ColorSettingDelegate.qml";
}
