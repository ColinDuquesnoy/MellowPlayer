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
    public:
        Updater(IReleaseQuerier& releaseQuerier, Settings& settings);

        void setCurrentRelease(const Release* currentRelease);

        void check();
        void download();
        void install();

        bool isUpdateAvailable() const;
        bool canInstall() const;
        const Release* getLatestRelease() const;

    signals:
        void updateAvailable();

    private slots:
        void onLatestReleaseReceived(const Release* release);

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
