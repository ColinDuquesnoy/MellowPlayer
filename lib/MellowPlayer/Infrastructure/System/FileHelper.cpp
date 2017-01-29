#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include "FileHelper.hpp"

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

string FileHelper::appDataDirectory() {
    auto retVal = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator();
    return retVal.toStdString();
}

string FileHelper::logDirectory() {
    auto retVal = QString::fromStdString(appDataDirectory()) + "Logs" + QDir::separator();
    return retVal.toStdString();
}

std::string FileHelper::createLogDirectory() {
    auto directory = logDirectory();
    QDir qDir(QString::fromStdString(directory));
    if (!qDir.exists())
        qDir.mkpath(qDir.path());
    return directory;
}
