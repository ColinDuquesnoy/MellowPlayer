#pragma once

#include "Release.hpp"
#include "UpdateChannel.hpp"
#include <QtCore/QObject>

namespace MellowPlayer::Application
{
    class IReleaseQuerier;
    class IPlatformUpdater;
    class Settings;
    class Setting;
    class ILogger;
    class AbstractPlatformUpdater;

    class Updater : public QObject
    {
        Q_OBJECT
        Q_ENUMS(Status)
    public:
        Updater(IReleaseQuerier &releaseQuerier, Settings &settings, AbstractPlatformUpdater &platformUpdater);

        enum class Status
        {
            None,
            Checking,
            UpdateAvailable,
            Downloading,
            Installing,
            Installed,
            Failure
        };

        void setCurrentRelease(const Release *currentRelease);

        bool isUpdateAvailable() const;
        bool canInstall() const;
        const Release *getLatestRelease() const;
        Status getStatus() const;

    public slots:
        void check();
        void install();
        void restart();

    signals:
        void updateAvailable();
        void noUpdateAvailable();
        void statusChanged();
        void progressUpdated(double progress);
        void installed();

    private slots:
        void onLatestReleaseReceived(const Release *release);
        void setStatus(Status status);
        void onDownloadFinished(bool succes);
        void onInstallFinished(bool succes);

    private:
        ILogger &logger_;
        IReleaseQuerier &releaseQuerier_;
        AbstractPlatformUpdater &platformUpdater_;
        Setting &autoCheckEnabledSetting_;
        Setting &updateChannelSetting_;
        bool isUpdateAvailable_ = false;
        const Release *currentRelease_;
        const Release *latestRelease_ = nullptr;

        MellowPlayer::Application::UpdateChannel getChannel() const;
        Status status_ = Status::None;
    };
}
