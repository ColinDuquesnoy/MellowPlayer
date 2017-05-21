#pragma once

#include <memory>
#include <QObject>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, StreamingServicePlugin)

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IStreamingServicePluginLoader: public QObject {
public:
    virtual ~IStreamingServicePluginLoader() = default;

    virtual QList<std::shared_ptr<MellowPlayer::Entities::StreamingServicePlugin>> load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
