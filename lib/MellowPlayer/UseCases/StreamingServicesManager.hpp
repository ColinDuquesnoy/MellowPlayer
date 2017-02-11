#pragma once
#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include "IStreamingServicesLoader.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class StreamingServicesManager: public QObject {
    Q_OBJECT
    Q_PROPERTY(StreamingService* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
public:
    StreamingServicesManager(IStreamingServicesLoader& pluginLoader);

    StreamingService& getService(const QString &name) const;
    const StreamingServicesList& getServices() const;
    void load();
    void setCurrentService(StreamingService* service);
    StreamingService* getCurrentService() const;

signals:
    void serviceAdded(StreamingService *plugin);
    void serviceRemoved(StreamingService *plugin);
    void currentServiceChanged(StreamingService* service);

private:
    IStreamingServicesLoader& pluginLoader;
    StreamingServicesList streamingServices;
    StreamingService* currentService;
};

END_MELLOWPLAYER_NAMESPACE
