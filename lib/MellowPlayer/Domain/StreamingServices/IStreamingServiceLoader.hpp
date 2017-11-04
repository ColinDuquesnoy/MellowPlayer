#pragma once

#include <QObject>
#include <memory>

namespace MellowPlayer::Domain
{
    class StreamingService;

    class IStreamingServiceLoader : public QObject
    {
    public:
        virtual ~IStreamingServiceLoader() = default;

        virtual QList<std::shared_ptr<MellowPlayer::Domain::StreamingService>> load() const = 0;
    };
}
