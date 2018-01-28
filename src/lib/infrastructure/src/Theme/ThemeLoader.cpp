#include <MellowPlayer/Infrastructure/Theme/ThemeLoader.hpp>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <MellowPlayer/Domain/Theme/Theme.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

Theme ThemeLoader::load(const QString& path) const
{
    Theme theme;

    if (QFileInfo(path).exists()) {
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QJsonDocument document = QJsonDocument::fromJson(file.readAll().data());
            QJsonObject object = document.object();
            theme.accent = object.value("accent").toString();
            theme.background = object.value("background").toString();
            theme.foreground = object.value("foreground").toString();
            theme.primary = object.value("primary").toString();
            theme.primaryForeground = object.value("primaryForeground").toString();
            theme.secondary = object.value("secondary").toString();
            theme.secondaryForeground = object.value("secondaryForeground").toString();
        }
    }

    return theme;
}
