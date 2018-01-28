#include <MellowPlayer/Infrastructure/Updater/Windows/WindowsUpdater.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <QApplication>
#include <QtCore/QDir>
#include <QtCore/QProcessEnvironment>

using namespace MellowPlayer::Infrastructure;

WindowsUpdater::WindowsUpdater(IFileDownloader& fileDownloader) : AbstractPlatformUpdater(fileDownloader)
{
}

bool WindowsUpdater::canInstall() const
{
    return asset_.isValid() && asset_.isWindowsInstaller();
}

void WindowsUpdater::doInstall(const QString& assetLocalPath)
{
    installerPath_ = assetLocalPath;
    // no installation here, we'll start the installer when user clicked on restart
    emit installFinished(QFile::exists(installerPath_));
}

QString WindowsUpdater::assetUrl() const
{
    return asset_.url();
}

QString WindowsUpdater::assetFileName() const
{
    return asset_.name();
}

void WindowsUpdater::setRelease(const Release* release)
{
    AbstractPlatformUpdater::setRelease(release);

    if (release_ != nullptr) {
        for (auto& asset : release_->assets()) {
            if (asset.isWindowsInstaller()) {
                asset_ = asset;
                break;
            }
        }
    }
}

void WindowsUpdater::restart()
{
    QProcess::startDetached(installerPath_);
    qApp->quit();
}
