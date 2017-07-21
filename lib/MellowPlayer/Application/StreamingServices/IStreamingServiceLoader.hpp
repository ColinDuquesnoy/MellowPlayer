#pragma once

#include <QObject>
#include <memory>

namespace MellowPlayer::Application
{
    class StreamingService;

    class IStreamingServiceLoader : public QObject
    {
    public:
        virtual ~IStreamingServiceLoader() = default;

        virtual QList<std::shared_ptr<MellowPlayer::Application::StreamingService>> load() const = 0;
    };
}
