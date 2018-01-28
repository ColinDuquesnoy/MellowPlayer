#include <MellowPlayer/Infrastructure/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Infrastructure/Network/IFileDownloader.hpp>
#include <QTemporaryDir>

using namespace MellowPlayer::Infrastructure;

AbstractPlatformUpdater::AbstractPlatformUpdater(IFileDownloader& fileDownloader) : fileDownloader_(fileDownloader)
{
    connect(&fileDownloader, &IFileDownloader::progressChanged, this, &AbstractPlatformUpdater::progressUpdated);
    connect(&fileDownloader, &IFileDownloader::finished, this, &AbstractPlatformUpdater::downloadFinished);
}

void AbstractPlatformUpdater::setRelease(const Release* release)
{
    release_ = release;
}

void AbstractPlatformUpdater::download()
{
    if (release_) {
        assetFilePath_ = makeDestinationPath();
        fileDownloader_.download(assetUrl(), assetFilePath_);
    }
}

QString AbstractPlatformUpdater::makeDestinationPath()
{
    QString tempDir = QTemporaryDir().path();
    QDir().mkpath(tempDir);
    return tempDir + "/" + assetFileName();
}

void AbstractPlatformUpdater::install()
{
    emit progressUpdated(-1);
    doInstall(assetFilePath_);
}
