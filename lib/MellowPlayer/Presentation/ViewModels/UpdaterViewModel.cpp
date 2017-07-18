#include "UpdaterViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


UpdaterViewModel::UpdaterViewModel(Updater& updater): updater_(updater) {
    connect(&updater, &Updater::updateAvailable, this, &UpdaterViewModel::onUpdateAvailable);
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

void UpdaterViewModel::close() {
    setVisible(false);
}

void UpdaterViewModel::check() {
    updater_.check();
}

void UpdaterViewModel::install() {
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

void UpdaterViewModel::onUpdateAvailable() {
    setCanInstall(updater_.canInstall());
    setProgress(-1);
    setVisible(true);
}
