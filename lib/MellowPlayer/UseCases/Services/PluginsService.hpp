#pragma once

#include <memory>
#include <QObject>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_STRUCT(Entities, Plugin)

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)


class ILogger;
class IPluginLoader;

class PluginsService: public QObject {
    Q_OBJECT
    Q_PROPERTY(Entities::Plugin* currentPlugin READ getCurrent WRITE setCurrent NOTIFY currentPluginChanged)
public:
    PluginsService(IPluginLoader& pluginLoader);

    void load();
    Entities::Plugin& get(const QString& name) const;
    const QList<std::shared_ptr<MellowPlayer::Entities::Plugin>>& getAll() const;
    
    void setCurrent(Entities::Plugin* plugin);
    Entities::Plugin* getCurrent() const;

signals:
    void pluginAdded(Entities::Plugin* plugin);
    void currentPluginChanged(Entities::Plugin* service);

private:
    ILogger& logger;
    IPluginLoader& pluginLoader;
    QList<std::shared_ptr<MellowPlayer::Entities::Plugin>> pluginList;
    Entities::Plugin* currentPlugin;
};

END_MELLOWPLAYER_NAMESPACE
