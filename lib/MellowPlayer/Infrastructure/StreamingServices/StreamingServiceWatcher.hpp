#pragma once

#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QMap>

namespace MellowPlayer::Domain
{
    class ILogger;
    class StreamingService;
}

namespace MellowPlayer::Infrastructure
{
    class StreamingServiceWatcher : public Domain::IStreamingServiceWatcher
    {
        Q_OBJECT
    public:
        StreamingServiceWatcher();

        void watch(Domain::StreamingService& serviceToWatch) override;

    private slots:
        void onFileChanged(const QString& path);

    private:
        void watchPath(const QString& path);

        class PluginInfo : public QObject
        {
        public:
            Domain::StreamingService& service_;
            QString scriptPath_;
            QString themePath_;

            PluginInfo(Domain::StreamingService& service, QString scriptPath, QString themePath, QObject* parent);
        };

        Domain::ILogger& logger_;
        QMap<QString, PluginInfo*> pluginInfo_;
        QFileSystemWatcher fileSystemWatcher_;
    };
}
