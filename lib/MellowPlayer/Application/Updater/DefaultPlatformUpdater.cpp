#include "DefaultPlatformUpdater.hpp"

using namespace MellowPlayer::Application;

DefaultPlatformUpdater::DefaultPlatformUpdater(IFileDownloader &downloader) : AbstractPlatformUpdater(downloader)
{
}

bool DefaultPlatformUpdater::canInstall() const
{
    return false;
}

void DefaultPlatformUpdater::doInstall(const QString &)
{
}

QString DefaultPlatformUpdater::getAssetUrl() const
{
    return "";
}

QString DefaultPlatformUpdater::getAssetFileName() const
{
    return "";
}
