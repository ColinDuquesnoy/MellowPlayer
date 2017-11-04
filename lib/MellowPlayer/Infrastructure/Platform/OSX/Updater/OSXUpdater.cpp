#include "OSXUpdater.hpp"
#include <MellowPlayer/Domain/Updater/Release.hpp>
#include <QApplication>
#include <QtCore/QDir>
#include <QtCore/QProcess>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

OSXUpdater::OSXUpdater(IFileDownloader& fileDownloader) : AbstractPlatformUpdater(fileDownloader)
{
}

bool OSXUpdater::canInstall() const
{
    return asset_.isValid() && asset_.isDmg();
}

void OSXUpdater::doInstall(const QString& assetLocalPath)
{
    // no real install step here, when restart is called we will show the dmg file in Finder.
    dmgPath_ = assetLocalPath;
    emit installFinished(QFile::exists(dmgPath_));
}

QString OSXUpdater::assetUrl() const
{
    return asset_.url();
}

QString OSXUpdater::assetFileName() const
{
    return asset_.name();
}

void OSXUpdater::setRelease(const Release* release)
{
    AbstractPlatformUpdater::setRelease(release);

    if (release_ != nullptr) {
        for (auto& asset : release_->assets()) {
            if (asset.isDmg()) {
                asset_ = asset;
                break;
            }
        }
    }
}
void OSXUpdater::restart()
{
    QStringList scriptArgs;
    scriptArgs << QLatin1String("-e") << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"").arg(dmgPath_);
    QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);

    scriptArgs.clear();
    scriptArgs << QLatin1String("-e") << QLatin1String("tell application \"Finder\" to activate");
    QProcess::execute("/usr/bin/osascript", scriptArgs);

    qApp->quit();
}
