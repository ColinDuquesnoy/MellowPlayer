#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "IReleaseQuerier.hpp"
#include "Release.hpp"
#include "Updater.hpp"

using namespace MellowPlayer::Application;

Updater::Updater(IReleaseQuerier& releaseQuerier, Settings& settings):
        logger_(LoggingManager::instance().getLogger("Updater")),
        releaseQuerier_(releaseQuerier),
        autoCheckEnabledSetting_(settings.get(SettingKey::MAIN_CHECK_FOR_UPDATES)),
        updateChannelSetting_(settings.get(SettingKey::MAIN_UPDATE_CHANNEL)),
        currentRelease_(&Release::current()) {
    releaseQuerier.setChannel(getChannel());
    connect(&releaseQuerier, &IReleaseQuerier::latestReceived, this, &Updater::onLatestReleaseReceived);
    connect(&updateChannelSetting_, &Setting::valueChanged, this, &Updater::check);

//    Release* r = new Release("1.95.0", QDate::fromString("2017-06-15"), this);
//    setCurrentRelease(r);
}

void Updater::check() {
    LOG_DEBUG(logger_, "Checking for update");
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
    LOG_DEBUG(logger_, "Latest release received: " + release->getName());

    if (release != nullptr && *release > *currentRelease_) {
        LOG_DEBUG(logger_, QString("Latest release is an update (%1 < %2)").arg(
                currentRelease_->getName()).arg(release->getName()));
        latestRelease_ = release;
        isUpdateAvailable_ = true;
        emit updateAvailable();
    }
    else {
        LOG_DEBUG(logger_, QString("No release found"));
        latestRelease_ = nullptr;
        isUpdateAvailable_ = false;
        emit noUpdateAvailable();
    }
}

void Updater::setCurrentRelease(const Release* currentRelease) {
    currentRelease_ = currentRelease;

}
