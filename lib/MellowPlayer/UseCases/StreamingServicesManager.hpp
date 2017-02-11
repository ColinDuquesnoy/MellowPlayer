#pragma once
#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include "IStreamingServicesLoader.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class StreamingServicesManager: public QObject {
    Q_OBJECT
    Q_PROPERTY(Entities::StreamingService* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
public:
    StreamingServicesManager(IStreamingServicesLoader& pluginLoader);

    Entities::StreamingService& getService(const QString &name) const;
    const Entities::StreamingServicesList& getServices() const;
    void load();
    void setCurrentService(Entities::StreamingService* service);
    Entities::StreamingService* getCurrentService() const;

signals:
    void serviceAdded(Entities::StreamingService *plugin);
    void serviceRemoved(Entities::StreamingService *plugin);
    void currentServiceChanged(Entities::StreamingService* service);

private:
    IStreamingServicesLoader& pluginLoader;
    Entities::StreamingServicesList streamingServices;
    Entities::StreamingService* currentService;
};

END_MELLOWPLAYER_NAMESPACE
