#pragma once

#include <memory>
#include <QObject>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, Plugin)

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IPluginLoader: public QObject {
public:
    virtual ~IPluginLoader() = default;

    virtual QList<std::shared_ptr<MellowPlayer::Entities::Plugin>> load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
