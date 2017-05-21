#include "StringSettingModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

StringSettingModel::StringSettingModel(Setting& setting, QObject* parent) : SettingModel(setting, parent) {

}

QString StringSettingModel::getValue() const {
    return setting.getValue().toString();
}

void StringSettingModel::setValue(QString value) {
    setting.setValue(value);
}

void StringSettingModel::onValueChanged() {
    emit valueChanged();
}
