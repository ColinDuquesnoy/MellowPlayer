#include "Updater.hpp"
#include "AbstractPlatformUpdater.hpp"
#include "IReleaseQuerier.hpp"
#include "Release.hpp"
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>

using namespace MellowPlayer::Application;

Updater::Updater(IReleaseQuerier &releaseQuerier, Settings &settings, AbstractPlatformUpdater &platformUpdater)
        : logger_(LoggingManager::instance().getLogger("Updater")),
          releaseQuerier_(releaseQuerier),
          platformUpdater_(platformUpdater),
          autoCheckEnabledSetting_(settings.get(SettingKey::MAIN_CHECK_FOR_UPDATES)),
          updateChannelSetting_(settings.get(SettingKey::MAIN_UPDATE_CHANNEL)),
          currentRelease_(&Release::current())
{
    releaseQuerier.setChannel(getChannel());
    connect(&releaseQuerier, &IReleaseQuerier::latestReceived, this, &Updater::onLatestReleaseReceived);
    connect(&updateChannelSetting_, &Setting::valueChanged, this, &Updater::check);

    Release *r = new Release("1.95.0", QDate::fromString("2017-06-15"), this);
    setCurrentRelease(r);
}

void Updater::check()
{
    LOG_DEBUG(logger_, "Checking for update");
    setStatus(Status::Checking);
    releaseQuerier_.setChannel(getChannel());
    releaseQuerier_.getLatest();
}

UpdateChannel Updater::getChannel() const
{
    return UpdateChannelStringer::fromString(updateChannelSetting_.getValue().toString());
}

void Updater::install()
{
    LOG_DEBUG(logger_, "Downloading update");
    setStatus(Status::Downloading);
    platformUpdater_.download();
}

bool Updater::isUpdateAvailable() const
{
    return isUpdateAvailable_;
}

bool Updater::canInstall() const
{
    return platformUpdater_.canInstall();
}

const Release *Updater::getLatestRelease() const
{
    return latestRelease_;
}

void Updater::onLatestReleaseReceived(const Release *release)
{
    LOG_DEBUG(logger_, "Latest release received: " + release->getName());
    setStatus(Status::None);

    if (release != nullptr && *release > *currentRelease_) {
        LOG_DEBUG(
        logger_,
        QString("Latest release is an update (%1 < %2)").arg(currentRelease_->getName()).arg(release->getName()));
        latestRelease_ = release;
        isUpdateAvailable_ = true;
        emit updateAvailable();
    } else {
        LOG_DEBUG(logger_, QString("No release found"));
        latestRelease_ = nullptr;
        isUpdateAvailable_ = false;
        emit noUpdateAvailable();
    }
}

void Updater::setCurrentRelease(const Release *currentRelease)
{
    currentRelease_ = currentRelease;
}

Updater::Status Updater::getStatus() const
{
    return status_;
}

void Updater::setStatus(Updater::Status status)
{
    if (status_ != status) {
        status_ = status;
        emit statusChanged();
    }
}

void Updater::onDownloadFinished(bool succes)
{
    if (succes) {
        setStatus(Status::Installing);
        platformUpdater_.install();
    } else {
        setStatus(Status::None);
    }
}
