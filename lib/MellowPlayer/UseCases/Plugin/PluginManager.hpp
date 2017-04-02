#pragma once

#include <memory>
#include <QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class Plugin;
class ILogger;
class IPluginLoader;

class PluginManager: public QObject {
    Q_OBJECT
    Q_PROPERTY(Plugin* currentPlugin READ getCurrent WRITE setCurrent NOTIFY currentPluginChanged)
public:
    PluginManager(IPluginLoader& pluginLoader);

    void load();
    Plugin& get(const QString& name) const;
    const QList<std::shared_ptr<MellowPlayer::UseCases::Plugin>>& getAll() const;
    
    void setCurrent(Plugin* plugin);
    UseCases::Plugin* getCurrent() const;

signals:
    void pluginAdded(Plugin* plugin);
    void currentPluginChanged(Plugin* service);

private:
    ILogger& logger;
    IPluginLoader& pluginLoader;
    QList<std::shared_ptr<MellowPlayer::UseCases::Plugin>> pluginList;
    Plugin* currentPlugin;
};

END_MELLOWPLAYER_NAMESPACE
