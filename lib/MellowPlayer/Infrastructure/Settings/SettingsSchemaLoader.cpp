#include "SettingsSchemaLoader.hpp"
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>

using namespace MellowPlayer::Infrastructure;

QJsonDocument SettingsSchemaLoader::load() const
{
    QFile jsonFile(":/MellowPlayer/Infrastructure/Settings/schema.json");
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}
