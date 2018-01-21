#include <MellowPlayer/Infrastructure/Updater/Linux/LinuxUpdater.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <QApplication>
#include <QDebug>
#include <QtCore/QDir>
#include <QtCore/QProcessEnvironment>

using namespace MellowPlayer::Infrastructure;

LinuxUpdater::LinuxUpdater(IFileDownloader& fileDownloader) : AbstractPlatformUpdater(fileDownloader)
{
}

bool LinuxUpdater::canInstall() const
{
    QString appImagePath = destinationDir();
    return asset_.isValid() && asset_.isAppImage() && !appImagePath.isEmpty();
}

QString LinuxUpdater::destinationDir() const
{
    QString appImagePath = qgetenv("APPIMAGE");
    if (!appImagePath.isEmpty())
        return QFileInfo(appImagePath).dir().absolutePath();
    return "";
}

void LinuxUpdater::doInstall(const QString& assetLocalPath)
{
    QString dest = destinationPath();
    QString backupPath = dest + ".backup";

    QFile::remove(backupPath);
    QFile::rename(dest, backupPath);
    QFile::copy(assetLocalPath, dest);

    QProcess::startDetached("chmod +x " + dest);

    emit installFinished(QFile::exists(dest));
}
QString LinuxUpdater::destinationPath() const
{
    QString dest = destinationDir();
    QString destinationPath = dest + "/" + assetFileName();
    return destinationPath;
}

QString LinuxUpdater::assetUrl() const
{
    return asset_.url();
}

QString LinuxUpdater::assetFileName() const
{
    return asset_.name();
}

void LinuxUpdater::setRelease(const Release* release)
{
    AbstractPlatformUpdater::setRelease(release);

    if (release_ != nullptr) {
        for (auto& asset : release_->assets()) {
            if (asset.isAppImage()) {
                asset_ = asset;
                break;
            }
        }
    }
}
void LinuxUpdater::restart()
{
    //    QFile file(destinationPath());
    //    QFile::setPermissions(destinationPath(), QFile::ExeUser | QFile::ExeOwner);
    QProcess::startDetached(destinationPath());
    qApp->quit();
}
