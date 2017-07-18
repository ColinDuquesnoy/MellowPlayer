#include "UpdaterViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


UpdaterViewModel::UpdaterViewModel(Updater& updater): updater_(updater) {
    connect(&updater, &Updater::updateAvailable, this, &UpdaterViewModel::onUpdateAvailable);
    connect(&updater, &Updater::noUpdateAvailable, this, &UpdaterViewModel::onNoUpdateAvailable);
}

QString UpdaterViewModel::getMessage() const {
    return message_;
}

bool UpdaterViewModel::isVisible() const {
    return visible_;
}

bool UpdaterViewModel::canInstall() const {
    return canInstall_;
}

int UpdaterViewModel::getProgress() const {
    return progress_;
}

bool UpdaterViewModel::isProgressVisible() const
{
    return progressVisible_;
}

void UpdaterViewModel::close() {
    setVisible(false);
}

void UpdaterViewModel::check() {
    setProgressVisible(true);
    setProgress(-1);
    updater_.check();
}

void UpdaterViewModel::install() {
    setMessage("Downloading update...");
    setProgressVisible(true);
    setProgress(-1);
    updater_.install();
}

void UpdaterViewModel::setVisible(bool visible) {
    if (visible_ == visible)
        return;

    visible_ = visible;
    emit visibleChanged();
}

void UpdaterViewModel::setCanInstall(bool canInstall) {
    if (canInstall_ == canInstall)
        return;

    canInstall_ = canInstall;
    emit canInstallChanged();
}

void UpdaterViewModel::setProgress(int progress) {
    if (progress_ == progress)
        return;

    progress_ = progress;
    emit progressChanged();
}

void UpdaterViewModel::setProgressVisible(bool progressVisible)
{
    if (progressVisible_ == progressVisible)
        return;

    progressVisible_ = progressVisible;
    emit progressVisibleChanged();
}

void UpdaterViewModel::onUpdateAvailable() {
    setCanInstall(updater_.canInstall());
    setProgressVisible(false);
    setProgress(-1);
    setVisible(true);
    setMessage(tr("A new version of <b>MellowPlayer</b> is available (%1)").arg(updater_.getLatestRelease()->getName()));
}

void UpdaterViewModel::onNoUpdateAvailable()
{
    setCanInstall(false);
    setProgressVisible(false);
    setProgress(-1);
    setVisible(false);
    setMessage("");
}

void UpdaterViewModel::setMessage(const QString& message) {
    if (message_ == message)
        return;
    message_ = message;
    emit messageChanged();
}

QString UpdaterViewModel::getUrl() const {
    return updater_.getLatestRelease()->getUrl();
}
