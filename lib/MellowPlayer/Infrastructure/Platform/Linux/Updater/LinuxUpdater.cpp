#include "LinuxUpdater.hpp"
#include <MellowPlayer/Application/Updater/Release.hpp>
#include <QApplication>
#include <QDebug>
#include <QtCore/QDir>
#include <QtCore/QProcessEnvironment>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

LinuxUpdater::LinuxUpdater(IFileDownloader& fileDownloader) : AbstractPlatformUpdater(fileDownloader)
{
}

bool LinuxUpdater::canInstall() const
{
    QString appImagePath = getDestinationDir();
    return asset_.isValid() && asset_.isAppImage() && !appImagePath.isEmpty();
}

QString LinuxUpdater::getDestinationDir() const
{
    QString appImagePath = qgetenv("APPIMAGE");
    if (!appImagePath.isEmpty())
        return QFileInfo(appImagePath).dir().absolutePath();
    return "";
}

void LinuxUpdater::doInstall(const QString& assetLocalPath)
{
    QString destinationPath = getDestinationPath();
    QString backupPath = destinationPath + ".backup";

    QFile::remove(backupPath);
    QFile::rename(destinationPath, backupPath);
    QFile::copy(assetLocalPath, destinationPath);

    QProcess::startDetached("chmod +x " + destinationPath);

    emit installFinished(QFile::exists(destinationPath));
}
QString LinuxUpdater::getDestinationPath() const
{
    QString destinationDir = getDestinationDir();
    QString destinationPath = destinationDir + "/" + getAssetFileName();
    return destinationPath;
}

QString LinuxUpdater::getAssetUrl() const
{
    return asset_.getUrl();
}

QString LinuxUpdater::getAssetFileName() const
{
    return asset_.getName();
}

void LinuxUpdater::setRelease(const Release* release)
{
    AbstractPlatformUpdater::setRelease(release);

    if (release_ != nullptr) {
        for (auto& asset : release_->getAssets()) {
            if (asset.isAppImage()) {
                asset_ = asset;
                break;
            }
        }
    }
}
void LinuxUpdater::restart()
{
    //    QFile file(getDestinationPath());
    //    QFile::setPermissions(getDestinationPath(), QFile::ExeUser | QFile::ExeOwner);
    QProcess::startDetached(getDestinationPath());
    qApp->quit();
}
