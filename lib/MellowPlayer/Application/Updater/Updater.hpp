#pragma once

#include <QtCore/QObject>
#include "Release.hpp"
#include "UpdateChannel.hpp"

namespace MellowPlayer::Application {

    class IReleaseQuerier;
    class IPlatformUpdater;
    class Settings;
    class Setting;
    class ILogger;

    class Updater: public QObject {
        Q_OBJECT
        Q_PROPERTY(bool isUpdateAvailable READ isUpdateAvailable NOTIFY isUpdateAvailableChanged)
        Q_PROPERTY(bool isDownloading READ isDownloading NOTIFY isDownloadingChanged)
        Q_PROPERTY(int downloadProgress READ getDownloadProgress NOTIFY downloadProgressChanged)
        Q_PROPERTY(bool canInstall READ canInstall CONSTANT)
        Q_PROPERTY(const Release* latestRelease READ getLatestRelease NOTIFY latestReleaseChanged)

    public:
        Updater(IReleaseQuerier& releaseQuerier, /*IPlatformUpdater& platformUpdater,*/ Settings& settings,
                const Release& currentRelease=Release::current());

        void check();
        void download();
        void install();

        bool isUpdateAvailable() const;
        bool isDownloading() const;
        bool canInstall() const;
        int getDownloadProgress() const;
        const Release* getLatestRelease() const;

    signals:
        void isUpdateAvailableChanged();
        void isDownloadingChanged();
        void downloadProgressChanged();
        void latestReleaseChanged();

    private slots:
        void onLatestReceived(const Release* release);

    private:
        ILogger& logger_;
        IReleaseQuerier& releaseQuerier_;
//        IPlatformUpdater& platformUpdater_;
        Setting& autoCheckEnabledSetting_;
        Setting& updateChannelSetting_;
        bool isUpdateAvailable_ = false;
        bool isDownloading_ = false;
        const Release* latestRelease_ = nullptr;

        MellowPlayer::Application::UpdateChannel getChannel() const;

    };
}
