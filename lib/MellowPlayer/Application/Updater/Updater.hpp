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
//        Q_ENUMS()
    public:
        Updater(IReleaseQuerier& releaseQuerier, Settings& settings);

//        enum class Status {
//            None,
//            Checking,
//            Downloading,
//            Installing
//        };

        void setCurrentRelease(const Release* currentRelease);

        bool isUpdateAvailable() const;
        bool canInstall() const;
        const Release* getLatestRelease() const;

    public slots:
        void check();
        void download();
        void install();

    signals:
        void updateAvailable();
        void noUpdateAvailable();

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
        const Release* currentRelease_;
        const Release* latestRelease_ = nullptr;

        MellowPlayer::Application::UpdateChannel getChannel() const;
//        Status status_ = Status::None;

    };
}
