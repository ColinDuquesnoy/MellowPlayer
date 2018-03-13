#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ShortcutSettingViewModel.hpp>
#include <QtGui/QKeySequence>
#include <MellowPlayer/Domain/Settings/Setting.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

ShortcutSettingViewModel::ShortcutSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QString ShortcutSettingViewModel::getValue() const
{
    return setting_.value().toString();
}

void ShortcutSettingViewModel::setValue(QString value)
{
    setting_.setValue(value);
}

void ShortcutSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString ShortcutSettingViewModel::qmlComponent()
{
    return "Delegates/ShortcutSettingDelegate.qml";
}

QString ShortcutSettingViewModel::keySequenceToString(int keyInt, int modifiers)
{
    // check for a combination of user clicks
    if (modifiers & Qt::ShiftModifier)
        keyInt += Qt::SHIFT;
    if (modifiers & Qt::ControlModifier)
        keyInt += Qt::CTRL;
    if (modifiers & Qt::AltModifier)
        keyInt += Qt::ALT;
    if (modifiers & Qt::MetaModifier)
        keyInt += Qt::META;

    return QKeySequence(keyInt).toString(QKeySequence::PortableText);
}

bool ShortcutSettingViewModel::isValidKeySequence(int key, int modifiers)
{
    if (keySequenceToString(key, modifiers).startsWith("F"))
        return true;
    if (modifiers == 0)
        return false;
    if (key == Qt::Key_unknown)
        return false;
    return !(key == Qt::Key_Control || key == Qt::Key_Shift || key == Qt::Key_Alt || key == Qt::Key_Meta);
}
