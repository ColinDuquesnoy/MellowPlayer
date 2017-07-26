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
            Application::StreamingService& service;
            QString scriptPath;
            QString themePath;

            PluginInfo(Application::StreamingService& service, QString scriptPath, QString themePath, QObject* parent)
                    : QObject(parent), service(service), scriptPath(scriptPath), themePath(themePath)
            {
            }
        };

        Application::ILogger& logger;
        QMap<QString, PluginInfo*> pluginInfos;
        QFileSystemWatcher fileSystemWatcher;
    };
}
