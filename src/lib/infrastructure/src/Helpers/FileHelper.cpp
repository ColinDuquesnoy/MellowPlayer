#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>

using namespace MellowPlayer::Infrastructure;
using namespace std;

QString FileHelper::appDataDirectory()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator();
}

QString FileHelper::logDirectory()
{
    return appDataDirectory() + "Logs" + QDir::separator();
}

QString FileHelper::createLogDirectory()
{
    auto directory = logDirectory();
    QDir qDir(directory);
    qDir.mkpath(qDir.path());
    return directory;
}

QString FileHelper::userScriptsDirectory() {
    return appDataDirectory() + "UserScripts" + QDir::separator();
}
