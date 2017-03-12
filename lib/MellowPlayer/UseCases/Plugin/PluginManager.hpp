#pragma once
#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include "../Interfaces/IPluginLoader.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PluginManager: public QObject {
    Q_OBJECT
    Q_PROPERTY(Plugin* currentPlugin READ getCurrent WRITE setCurrent NOTIFY currentPluginChanged)
public:
    PluginManager(IPluginLoader& pluginLoader);

    void load();
    Plugin& get(const QString& name) const;
    const PluginList& getAll() const;
    
    void setCurrent(Plugin* plugin);
    UseCases::Plugin* getCurrent() const;

signals:
    void pluginAdded(Plugin* plugin);
    void currentPluginChanged(Plugin* service);

private:
    ILogger& logger;
    IPluginLoader& pluginLoader;
    PluginList pluginList;
    Plugin* currentPlugin;
};

END_MELLOWPLAYER_NAMESPACE
