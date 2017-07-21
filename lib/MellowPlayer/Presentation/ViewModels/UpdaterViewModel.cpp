#include <MellowPlayer/Presentation/Converters/UpdaterStatusConverter.hpp>
#include "UpdaterViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


UpdaterViewModel::UpdaterViewModel(Updater& updater): updater_(updater)
{
    connect(&updater, &Updater::updateAvailable, this, &UpdaterViewModel::onUpdateAvailable);
    connect(&updater, &Updater::noUpdateAvailable, this, &UpdaterViewModel::onNoUpdateAvailable);
    connect(&updater, &Updater::statusChanged, this, &UpdaterViewModel::statusChanged);
    connect(&updater, &Updater::statusChanged, this, &UpdaterViewModel::busyChanged);
    connect(&updater, &Updater::statusChanged, this, &UpdaterViewModel::updateMessage);
    emit statusChanged();
    emit busyChanged();
}

QString UpdaterViewModel::getMessage() const
{
    return message_;
}

bool UpdaterViewModel::isVisible() const
{
    return visible_;
}

bool UpdaterViewModel::isInstallEnabled() const
{
    return installEnabled_;
}

int UpdaterViewModel::getProgress() const
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
    setProgress(-1);
    updater_.install();
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

void UpdaterViewModel::setProgress(int progress)
{
    if (progress_ == progress)
        return;

    progress_ = progress;
    emit progressChanged();
}

void UpdaterViewModel::onUpdateAvailable()
{
    setInstallEnabled(updater_.canInstall());
    setProgress(-1);
    setVisible(true);
    updateMessage();
}

void UpdaterViewModel::onNoUpdateAvailable()
{
    setInstallEnabled(false);
    setProgress(-1);
    setVisible(false);
    updateMessage();
}

void UpdaterViewModel::setMessage(const QString& message)
{
    if (message_ == message)
        return;
    message_ = message;
    emit messageChanged();
}

QString UpdaterViewModel::getUrl() const
{
    const Release* r = updater_.getLatestRelease();
    if (r != nullptr)
        return r->getUrl();
    return "";
}

QString UpdaterViewModel::getStatusString() const {
    return UpdaterStatusConverter::toString(updater_.getStatus());
}

bool UpdaterViewModel::isBusy() const {
    return updater_.getStatus() != Updater::Status::None;
}

void UpdaterViewModel::updateMessage() {
    if (updater_.getStatus() == Updater::Status::None && updater_.isUpdateAvailable()) {
        setMessage(tr("A new version of <b>MellowPlayer</b> is available (%1)").arg(
                updater_.getLatestRelease()->getName()));
    }
    else
        setMessage(getStatusString());

}
