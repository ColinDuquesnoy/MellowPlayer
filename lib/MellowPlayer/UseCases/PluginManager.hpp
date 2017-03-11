#pragma once
#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities.hpp>
#include "Interfaces/IPluginLoader.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PluginManager: public QObject {
    Q_OBJECT
    Q_PROPERTY(Entities::Plugin* currentPlugin READ getCurrentPlugin WRITE setCurrentPlugin NOTIFY currentPluginChanged)
public:
    PluginManager(IPluginLoader& pluginLoader);

    void load();
    Entities::Plugin& get(const QString& name) const;
    const Entities::PluginList& getServices() const;
    
    void setCurrentPlugin(Entities::Plugin* plugin);
    Entities::Plugin* getCurrentPlugin() const;

signals:
    void pluginAdded(Entities::Plugin* plugin);
    void currentPluginChanged(Entities::Plugin* service);

private:
    IPluginLoader& pluginLoader;
    Entities::PluginList pluginList;
    Entities::Plugin* currentPlugin;
};

END_MELLOWPLAYER_NAMESPACE
