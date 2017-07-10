#pragma once

#include <QtCore/QObject>
#include "StreamingService.hpp"

namespace MellowPlayer::Application {

    class IStreamingServiceWatcher: public QObject {
        Q_OBJECT
    public:
        virtual ~IStreamingServiceWatcher() = default;
        virtual void watch(StreamingService& serviceToWatch) = 0;
    };

}
