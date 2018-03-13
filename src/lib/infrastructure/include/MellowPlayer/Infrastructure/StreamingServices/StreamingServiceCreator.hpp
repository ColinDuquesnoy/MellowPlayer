#pragma once

#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <QtCore/QString>
#include <functional>

namespace MellowPlayer::Infrastructure
{
    class StreamingServiceCreator : public Domain::IStreamingServiceCreator
    {
    public:
        QString create(const QString& serviceName, const QString& serviceUrl, const QString& authorName, const QString& authorWebsite,
                       const QString& supportedPlatforms) const override;

    private:
        void createScript(const QString& pluginDir) const;
        void createLogo(const QString& pluginDir) const;
        void createTheme(const QString& pluginDir) const;
        void createMetadata(const QString& serviceName, const QString& serviceUrl, const QString& authorName, const QString& authorWebsite,
                            const QString& supportedPlatforms, const QString& pluginDir) const;
        QString pluginDir(const QString& serviceName) const;
        QString readTemplateFile(const QString& fileName) const;
        void write(const QString& path, const QString& content) const;
        QString filePath(const QString& pluginDir, const QString& fileName) const;
        void createPluginFile(const QString& pluginDir, const QString& fileName,
                              const std::function<QString(QString)>& transformer = [](QString string) { return string; }) const;

        static const QString RESOURCE_PATH;
        static const QString SCRIPT_FILE_NAME;
        static const QString LOGO_FILE_NAME;
        static const QString METADATA_FILE_NAME;
        static const QString THEME_FILE_NAME;
    };
}
