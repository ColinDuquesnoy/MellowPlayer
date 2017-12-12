#pragma once

#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilters.hpp>

namespace MellowPlayer::Domain
{
    class ILogger;
    class StreamingService;
    struct StreamingServiceMetadata;
    struct Theme;
}

namespace MellowPlayer::Infrastructure
{
    class StreamingServiceLoader : public Domain::IStreamingServiceLoader
    {
    public:
        StreamingServiceLoader();
        QList<std::shared_ptr<Domain::StreamingService>> load() const override;

        static QString userDirectory();

        static Domain::Theme readTheme(const QString& filePath);
        static QString readFileContent(const QString& filePath);

    private:
        std::unique_ptr<Domain::StreamingService> loadService(const QString& directory) const;
        QString findFileByExtension(const QString& directory, const QString& suffix) const;
        Domain::StreamingServiceMetadata readMetadata(const QString& filePath) const;
        bool checkServiceDirectory(const QString& directory) const;
        QStringList searchPaths() const;
        bool containsService(const QList<std::shared_ptr<Domain::StreamingService>>& services,
                             std::shared_ptr<Domain::StreamingService>& toCheck) const;

        Domain::ILogger& logger_;
        PlatformFilters platformFilters_;
    };
}
