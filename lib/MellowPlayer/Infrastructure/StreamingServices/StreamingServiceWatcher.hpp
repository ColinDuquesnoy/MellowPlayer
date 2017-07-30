#pragma once

#include <MellowPlayer/Application/StreamingServices/IStreamingServiceWatcher.hpp>
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QMap>

namespace MellowPlayer::Application
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class StreamingServiceWatcher : public Application::IStreamingServiceWatcher
    {
        Q_OBJECT
    public:
        StreamingServiceWatcher();

        void watch(Application::StreamingService& serviceToWatch) override;

    private slots:
        void onFileChanged(const QString& path);

    private:
        void watchPath(const QString& path);

        class PluginInfo : public QObject
        {
        public:
            Application::StreamingService& service_;
            QString scriptPath_;
            QString themePath_;

            PluginInfo(Application::StreamingService& service, QString scriptPath, QString themePath, QObject* parent)
                    : QObject(parent), service_(service), scriptPath_(scriptPath), themePath_(themePath)
            {
            }
        };

        Application::ILogger& logger_;
        QMap<QString, PluginInfo*> pluginInfo_;
        QFileSystemWatcher fileSystemWatcher_;
    };
}
