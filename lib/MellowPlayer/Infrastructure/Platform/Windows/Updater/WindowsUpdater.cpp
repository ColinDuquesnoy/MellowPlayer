#include "WindowsUpdater.hpp"
#include <MellowPlayer/Application/Updater/Release.hpp>
#include <QApplication>
#include <QtCore/QDir>
#include <QtCore/QProcessEnvironment>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

WindowsUpdater::WindowsUpdater(IFileDownloader &fileDownloader) : AbstractPlatformUpdater(fileDownloader)
{
}

bool WindowsUpdater::canInstall() const
{
    return asset_.isValid() && asset_.isWindowsInstaller();
}

void WindowsUpdater::doInstall(const QString &assetLocalPath)
{
    installerPath_ = assetLocalPath;
    // no installation here, we'll start the installer when user clicked on restart
    emit installFinished(QFile::exists(installerPath_));
}

QString WindowsUpdater::getAssetUrl() const
{
    return asset_.getUrl();
}

QString WindowsUpdater::getAssetFileName() const
{
    return asset_.getName();
}

void WindowsUpdater::setRelease(const Release *release)
{
    AbstractPlatformUpdater::setRelease(release);

    if (release_ != nullptr) {
        for (auto &asset : release_->getAssets()) {
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
