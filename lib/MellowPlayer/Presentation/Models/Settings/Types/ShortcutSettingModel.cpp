#include <QtGui/QKeySequence>
#include "ShortcutSettingModel.hpp"
#include <QDebug>

USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

ShortcutSettingModel::ShortcutSettingModel(Setting& setting, QObject* parent) : SettingModel(setting, parent) {

}

QString ShortcutSettingModel::getValue() const {
    return setting.getValue().toString();
}

void ShortcutSettingModel::setValue(QString value) {
    setting.setValue(value);
}

void ShortcutSettingModel::onValueChanged() {
    emit valueChanged();
}

QString ShortcutSettingModel::getQmlComponent() {
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/ShortcutSettingDelegate.qml";
}

QString ShortcutSettingModel::keySequenceToString(int keyInt, int modifiers)
{
        // check for a combination of user clicks
    if(modifiers & Qt::ShiftModifier)
        keyInt += Qt::SHIFT;
    if(modifiers & Qt::ControlModifier)
        keyInt += Qt::CTRL;
    if(modifiers & Qt::AltModifier)
        keyInt += Qt::ALT;
    if(modifiers & Qt::MetaModifier)
        keyInt += Qt::META;

    qDebug() << "New KeySequence:" << QKeySequence(keyInt).toString(QKeySequence::PortableText);
    return QKeySequence(keyInt).toString(QKeySequence::PortableText);
}

bool ShortcutSettingModel::isValidKeySequence(int key, int modifiers)
{
    if (modifiers == 0)
        return false;
    if(key == Qt::Key_unknown)
        return false;
    if(key == Qt::Key_Control || key == Qt::Key_Shift || key == Qt::Key_Alt || key == Qt::Key_Meta)
        return false;
    return true;
}
