#pragma once

#include <memory>
#include <QObject>
#include <QList>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, StreamingServicePlugin)

BEGIN_MELLOWPLAYER_NAMESPACE(Application)


class ILogger;
class IStreamingServicePluginLoader;

class StreamingServicePluginService: public QObject {
    Q_OBJECT
    Q_PROPERTY(Entities::StreamingServicePlugin* currentPlugin READ getCurrent WRITE setCurrent NOTIFY currentPluginChanged)
public:
    StreamingServicePluginService(IStreamingServicePluginLoader& pluginLoader);

    void load();
    Entities::StreamingServicePlugin& get(const QString& name) const;
    const QList<std::shared_ptr<Entities::StreamingServicePlugin>>& getAll() const { return pluginList; }
    
    void setCurrent(Entities::StreamingServicePlugin* plugin);
    Entities::StreamingServicePlugin* getCurrent() const;

signals:
    void pluginAdded(Entities::StreamingServicePlugin* plugin);
    void currentPluginChanged(Entities::StreamingServicePlugin* service);

private:
    ILogger& logger;
    IStreamingServicePluginLoader& pluginLoader;
    QList<std::shared_ptr<MellowPlayer::Entities::StreamingServicePlugin>> pluginList;
    Entities::StreamingServicePlugin* currentPlugin;
};

END_MELLOWPLAYER_NAMESPACE
