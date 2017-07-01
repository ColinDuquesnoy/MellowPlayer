#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include "FileHelper.hpp"

USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

QString FileHelper::appDataDirectory() {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator();
}

QString FileHelper::logDirectory() {
    return appDataDirectory() + "Logs" + QDir::separator();
}

QString FileHelper::createLogDirectory() {
    auto directory = logDirectory();
    QDir qDir(directory);
    qDir.mkpath(qDir.path());
    return directory;
}
