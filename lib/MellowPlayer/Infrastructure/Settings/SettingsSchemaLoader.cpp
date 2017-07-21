#include "SettingsSchemaLoader.hpp"
#include <QtCore/QFile>

using namespace MellowPlayer::Infrastructure;

QJsonDocument SettingsSchemaLoader::load() const
{
    QFile jsonFile(":/MellowPlayer/Application/Settings/schema.json");
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}
