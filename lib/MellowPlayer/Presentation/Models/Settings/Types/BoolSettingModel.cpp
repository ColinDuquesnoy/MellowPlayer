#include "BoolSettingModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Application)

BoolSettingModel::BoolSettingModel(Setting& setting, QObject* parent) : SettingModel(setting, parent) {

}

bool BoolSettingModel::getValue() const {
    return setting.getValue().toBool();
}

void BoolSettingModel::setValue(bool value) {
    setting.setValue(value);
}

void BoolSettingModel::onValueChanged() {
    emit valueChanged();
}

QString BoolSettingModel::getQmlComponent() {
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/BoolSettingDelegate.qml";
}
