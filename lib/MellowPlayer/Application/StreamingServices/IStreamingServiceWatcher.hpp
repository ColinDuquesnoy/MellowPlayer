#pragma once

#include "StreamingService.hpp"
#include <QtCore/QObject>

namespace MellowPlayer::Application
{
    class IStreamingServiceWatcher : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IStreamingServiceWatcher() = default;
        virtual void watch(StreamingService& serviceToWatch) = 0;
    };
}
