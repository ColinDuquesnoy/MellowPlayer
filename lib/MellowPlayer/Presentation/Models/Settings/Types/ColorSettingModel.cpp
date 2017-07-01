#include "ColorSettingModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Presentation)
USING_MELLOWPLAYER_NAMESPACE(Application)

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
