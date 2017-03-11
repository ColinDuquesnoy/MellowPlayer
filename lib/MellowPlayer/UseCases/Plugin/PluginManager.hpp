#pragma once
#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities.hpp>
#include "MellowPlayer/UseCases/Interfaces/IPluginLoader.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PluginManager: public QObject {
    Q_OBJECT
    Q_PROPERTY(UseCases::Plugin* currentPlugin READ getCurrent WRITE setCurrent NOTIFY currentPluginChanged)
public:
    PluginManager(IPluginLoader& pluginLoader);

    void load();
    UseCases::Plugin& get(const QString& name) const;
    const UseCases::PluginList& getAll() const;
    
    void setCurrent(UseCases::Plugin* plugin);
    UseCases::Plugin* getCurrent() const;

signals:
    void pluginAdded(UseCases::Plugin* plugin);
    void currentPluginChanged(UseCases::Plugin* service);

private:
    IPluginLoader& pluginLoader;
    UseCases::PluginList pluginList;
    UseCases::Plugin* currentPlugin;
};

END_MELLOWPLAYER_NAMESPACE
