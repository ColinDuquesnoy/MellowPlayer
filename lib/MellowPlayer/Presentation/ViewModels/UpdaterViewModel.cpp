#include "UpdaterViewModel.hpp"
#include <MellowPlayer/Presentation/Converters/UpdaterStatusConverter.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

UpdaterViewModel::UpdaterViewModel(Updater& updater) : updater_(updater)
{
    connect(&updater, &Updater::updateAvailable, this, &UpdaterViewModel::onUpdateAvailable);
    connect(&updater, &Updater::noUpdateAvailable, this, &UpdaterViewModel::onNoUpdateAvailable);
    connect(&updater, &Updater::statusChanged, this, &UpdaterViewModel::statusChanged);
    connect(&updater, &Updater::statusChanged, this, &UpdaterViewModel::busyChanged);
    connect(&updater, &Updater::progressUpdated, this, &UpdaterViewModel::onProgressUpdated);
    connect(&updater, &Updater::installed, this, &UpdaterViewModel::onInstalled);
    emit statusChanged();
    emit busyChanged();
}

bool UpdaterViewModel::isVisible() const
{
    return visible_;
}

bool UpdaterViewModel::isInstallEnabled() const
{
    return installEnabled_;
}

double UpdaterViewModel::getProgress() const
{
    return progress_;
}

void UpdaterViewModel::close()
{
    setVisible(false);
}

void UpdaterViewModel::check()
{
    setProgress(-1);
    updater_.check();
}

void UpdaterViewModel::install()
{
    setInstallEnabled(false);
    setRestartEnabled(false);
    setProgress(-1);
    updater_.install();
}

void UpdaterViewModel::restart()
{
    setInstallEnabled(false);
    setRestartEnabled(false);
    setProgress(-1);
    setVisible(false);
    updater_.restart();
}

void UpdaterViewModel::setVisible(bool visible)
{
    if (visible_ == visible)
        return;

    visible_ = visible;
    emit visibleChanged();
}

void UpdaterViewModel::setInstallEnabled(bool enabled)
{
    if (installEnabled_ == enabled)
        return;

    installEnabled_ = enabled;
    emit installEnabledChanged();
}

void UpdaterViewModel::setProgress(double progress)
{
    if (progress_ == progress)
        return;

    progress_ = progress;
    emit progressChanged();
}

void UpdaterViewModel::onUpdateAvailable()
{
    setInstallEnabled(updater_.canInstall());
    setRestartEnabled(false);
    setProgress(-1);
    setVisible(true);
    ;
}

void UpdaterViewModel::onNoUpdateAvailable()
{
    setInstallEnabled(false);
    setRestartEnabled(false);
    setProgress(-1);
    setVisible(false);
}

QString UpdaterViewModel::getUrl() const
{
    const Release* r = updater_.getLatestRelease();
    if (r != nullptr)
        return r->getUrl();
    return "";
}

QString UpdaterViewModel::getStatusString() const
{
    return UpdaterStatusConverter::toString(updater_.getStatus());
}

bool UpdaterViewModel::isBusy() const
{
    return updater_.getStatus() == Updater::Status::Checking || updater_.getStatus() == Updater::Status::Downloading
    || updater_.getStatus() == Updater::Status::Installing;
}

void UpdaterViewModel::onProgressUpdated(double progress)
{
    setProgress(progress);
}
bool UpdaterViewModel::isRestartEnabled() const
{
    return restartEnabled_;
}
void UpdaterViewModel::setRestartEnabled(bool enabled)
{
    if (restartEnabled_ != enabled) {
        restartEnabled_ = enabled;
        emit restartEnabledChanged();
    }
}
void UpdaterViewModel::onInstalled()
{
    setInstallEnabled(false);
    setRestartEnabled(true);
}
