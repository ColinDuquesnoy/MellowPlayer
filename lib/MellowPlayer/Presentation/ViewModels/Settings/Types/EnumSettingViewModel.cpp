#include "EnumSettingViewModel.hpp"

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

EnumSettingViewModel::EnumSettingViewModel(Setting &setting, QObject *parent) : SettingViewModel(setting, parent)
{
}

QString EnumSettingViewModel::getValue() const
{
    return setting.getValue().toString();
}

void EnumSettingViewModel::setValue(QString value)
{
    setting.setValue(value);
}

void EnumSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString EnumSettingViewModel::getQmlComponent()
{
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/"
           "EnumSettingDelegate.qml";
}

QStringList EnumSettingViewModel::getValues() const
{
    QString list = setting.getType();
    list = list.replace("enum[", "").replace("]", "").replace("'", "").replace("\"", "").replace(" ", "");
    return list.split(",");
}
