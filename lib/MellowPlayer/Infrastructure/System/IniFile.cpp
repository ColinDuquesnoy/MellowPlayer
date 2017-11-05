#include "IniFile.hpp"
#include "../../../../../../../../usr/include/qt5/QtCore/QVariant"
#include "../../../../../../../../usr/include/qt5/QtCore/QString"

using namespace MellowPlayer::Infrastructure;

IniFile::IniFile(const QString& path): iniFile_(path, QSettings::IniFormat)
{

}

QVariant IniFile::value(const QString& key, const QVariant& defaultValue) const
{
    return iniFile_.value(key, defaultValue);
}
