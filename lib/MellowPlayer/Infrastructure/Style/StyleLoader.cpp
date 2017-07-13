#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include "StyleLoader.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

Style StyleLoader::load(const QString &path) const {
    Style style;

    if (QFileInfo(path).exists()) {
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QJsonDocument document = QJsonDocument::fromJson(file.readAll().data());
            QJsonObject object = document.object();
            style.accent = object.value("accent").toString();
            style.background = object.value("background").toString();
            style.foreground = object.value("foreground").toString();
            style.primary = object.value("primary").toString();
            style.primaryForeground = object.value("primaryForeground").toString();
            style.secondary = object.value("secondary").toString();
            style.secondaryForeground = object.value("secondaryForeground").toString();
        }
    }

    return style;
}
