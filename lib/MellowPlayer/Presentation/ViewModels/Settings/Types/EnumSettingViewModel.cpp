#include "EnumSettingViewModel.hpp"

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

EnumSettingViewModel::EnumSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QString EnumSettingViewModel::getValue() const
{
    return setting_.value().toString();
}

void EnumSettingViewModel::setValue(QString value)
{
    setting_.setValue(value);
}

void EnumSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString EnumSettingViewModel::qmlComponent()
{
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/EnumSettingDelegate.qml";
}

QStringList EnumSettingViewModel::values() const
{
    QString list = setting_.type();
    list = list.replace("enum[", "").replace("]", "").replace("'", "").replace("\"", "").replace(" ", "");
    return list.split(",");
}
