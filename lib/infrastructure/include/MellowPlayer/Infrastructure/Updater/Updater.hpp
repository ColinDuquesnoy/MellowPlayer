#pragma once

#include "UpdateChannel.hpp"
#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class ILogger;
    class Settings;
    class Setting;
}

namespace MellowPlayer::Infrastructure
{
    class AbstractPlatformUpdater;
    class ILatestReleaseQuerier;
    class Release;

    class Updater : public QObject
    {
        Q_OBJECT
        Q_ENUMS(Status)
    public:
        Updater(ILatestReleaseQuerier& releaseQuerier, Domain::Settings& settings, AbstractPlatformUpdater& platformUpdater);

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

        void setCurrentRelease(const Release* currentRelease);

        bool isUpdateAvailable() const;
        bool canInstall() const;
        const Release* latestRelease() const;
        Status status() const;

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
        void onLatestReleaseReceived(const Release* release);
        void setStatus(Status status);
        void onDownloadFinished(bool succes);
        void onInstallFinished(bool succes);

    private:
        UpdateChannel getChannel() const;

        Domain::ILogger& logger_;
        ILatestReleaseQuerier& releaseQuerier_;
        AbstractPlatformUpdater& platformUpdater_;
        Domain::Setting& autoCheckEnabledSetting_;
        Domain::Setting& updateChannelSetting_;
        bool isUpdateAvailable_ = false;
        const Release* currentRelease_;
        const Release* latestRelease_ = nullptr;
        Status status_ = Status::None;
    };
}
