#pragma once

#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class StreamingService;

    class IStreamingServiceWatcher : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IStreamingServiceWatcher() = default;
        virtual void watch(StreamingService& serviceToWatch) = 0;
    };
}
