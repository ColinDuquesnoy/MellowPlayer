#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "IReleaseQuerier.hpp"
#include "Release.hpp"
#include "Updater.hpp"

using namespace MellowPlayer::Application;

Updater::Updater(IReleaseQuerier& releaseQuerier, /*IPlatformUpdater& platformUpdater, */ Settings& settings,
                 const Release& currentRelease) :
        logger_(LoggingManager::instance().getLogger("Updater")),
        releaseQuerier_(releaseQuerier),
//        platformUpdater_(platformUpdater),
        autoCheckEnabledSetting_(settings.get(SettingKey::MAIN_CHECK_FOR_UPDATES)),
        updateChannelSetting_(settings.get(SettingKey::MAIN_UPDATE_CHANNEL)),
        latestRelease_(&currentRelease) {
    releaseQuerier.setChannel(getChannel());
    connect(&releaseQuerier, &IReleaseQuerier::latestReceived, this, &Updater::onLatestReleaseReceived);
}

void Updater::check() {
    LOG_DEBUG(logger_, "Checking for updated");
    releaseQuerier_.setChannel(getChannel());
    releaseQuerier_.getLatest();
}

UpdateChannel Updater::getChannel() const {
    return UpdateChannelStringer::fromString(updateChannelSetting_.getValue().toString());
}

void Updater::download() {
    LOG_DEBUG(logger_, "Downloading update");
    isDownloading_ = true;
//    platformUpdater_.download(latestRelease_);
}

void Updater::install() {
    LOG_DEBUG(logger_, "Installing update");
//    platformUpdater_.install(latestRelease_);
}

bool Updater::isUpdateAvailable() const {
    return isUpdateAvailable_;
}

bool Updater::canInstall() const {
//    return platformUpdater_.canInstall();
    return false;
}

const Release* Updater::getLatestRelease() const {
    return latestRelease_;
}

void Updater::onLatestReleaseReceived(const Release* release) {
    LOG_DEBUG(logger_, "Latest release received");

    if (*release > *latestRelease_) {
        LOG_DEBUG(logger_, QString("Latest release is an update (%1 < %2)").arg(
                latestRelease_->getName()).arg(release->getName()));
        latestRelease_ = release;
        isUpdateAvailable_ = true;
        emit updateAvailable();
    }
}
