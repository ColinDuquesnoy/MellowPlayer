#pragma once

#include <memory>
#include <QObject>

namespace MellowPlayer::Application {

    class StreamingService;

    class IStreamingServiceLoader: public QObject {
    public:
        virtual ~IStreamingServiceLoader() = default;

        virtual QList<std::shared_ptr<MellowPlayer::Application::StreamingService>> load() const = 0;
    };

}
