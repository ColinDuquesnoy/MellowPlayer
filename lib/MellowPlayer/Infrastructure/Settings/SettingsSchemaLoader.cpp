#include <QtCore/QFile>
#include "SettingsSchemaLoader.hpp"

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

QJsonDocument SettingsSchemaLoader::load() const {
    QFile jsonFile(":/MellowPlayer/UseCases/Settings/schema.json");
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}
