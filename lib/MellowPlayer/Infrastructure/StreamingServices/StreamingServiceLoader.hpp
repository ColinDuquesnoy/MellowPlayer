#pragma once

#include <MellowPlayer/Application/StreamingServices/IStreamingServiceLoader.hpp>

namespace MellowPlayer::Application {

    class ILogger;
    struct StreamingServiceMetadata;
    struct StreamingServiceStyle;
    
}
namespace MellowPlayer::Infrastructure {

    class StreamingServiceLoader: public Application::IStreamingServiceLoader {
    public:
        StreamingServiceLoader();
        QList<std::shared_ptr<Application::StreamingService>> load() const override;

        static QString getUserDirectory();

    private:
        std::unique_ptr<Application::StreamingService> loadService(const QString& directory) const;
        QString findFileByExtension(const QString &directory, const QString &suffix) const;
        QString readFileContent(const QString &filePath) const;
        Application::StreamingServiceMetadata readMetadata(const QString &filePath) const;
        Application::StreamingServiceStyle readStyle(const QString &filePath) const;
        bool checkServiceDirectory(const QString& directory) const;
        QStringList getSearchPaths() const;
        bool containsService(const QList<std::shared_ptr<Application::StreamingService>>& services,
                             std::shared_ptr<Application::StreamingService>& toCheck) const;

        Application::ILogger& logger;
    };

}
