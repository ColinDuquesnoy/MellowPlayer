#include "ColorSettingViewModel.hpp"

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

ColorSettingViewModel::ColorSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QColor ColorSettingViewModel::getValue() const
{
    return QColor(setting.getValue().toString());
}

void ColorSettingViewModel::setValue(QColor value)
{
    setting.setValue(value.name());
}

void ColorSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString ColorSettingViewModel::getQmlComponent()
{
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/"
           "ColorSettingDelegate.qml";
}
