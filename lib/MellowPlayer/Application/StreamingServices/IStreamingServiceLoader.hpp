#pragma once

#include <memory>
#include <QObject>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingService)

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class IStreamingServiceLoader: public QObject {
public:
    virtual ~IStreamingServiceLoader() = default;

    virtual QList<std::shared_ptr<MellowPlayer::Application::StreamingService>> load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
