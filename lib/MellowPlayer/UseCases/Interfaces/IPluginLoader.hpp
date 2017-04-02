#pragma once

#include <memory>
#include <QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class Plugin;

class IPluginLoader: public QObject {
public:
    virtual ~IPluginLoader() = default;

    virtual QList<std::shared_ptr<MellowPlayer::UseCases::Plugin>> load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
