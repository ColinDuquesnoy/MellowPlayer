#pragma once

#include <MellowPlayer/Application/StreamingServices/IStreamingServiceLoader.hpp>

namespace MellowPlayer::Application
{
    class ILogger;
    struct StreamingServiceMetadata;
    struct Theme;
}

namespace MellowPlayer::Infrastructure
{
    class StreamingServiceLoader : public Application::IStreamingServiceLoader
    {
    public:
        StreamingServiceLoader();
        QList<std::shared_ptr<Application::StreamingService>> load() const override;

        static QString getUserDirectory();

        static Application::Theme readTheme(const QString &filePath);
        static QString readFileContent(const QString &filePath);

    private:
        std::unique_ptr<Application::StreamingService> loadService(const QString &directory) const;
        QString findFileByExtension(const QString &directory, const QString &suffix) const;
        Application::StreamingServiceMetadata readMetadata(const QString &filePath) const;
        bool checkServiceDirectory(const QString &directory) const;
        QStringList getSearchPaths() const;
        bool containsService(const QList<std::shared_ptr<Application::StreamingService>> &services,
                             std::shared_ptr<Application::StreamingService> &toCheck) const;

        Application::ILogger &logger;
    };
}
