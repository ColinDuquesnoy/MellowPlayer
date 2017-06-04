#pragma once

#include <memory>
#include <QObject>
#include <QList>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingService)

BEGIN_MELLOWPLAYER_NAMESPACE(Application)


class ILogger;
class IStreamingServiceLoader;

class StreamingServices: public QObject {
    Q_OBJECT
    Q_PROPERTY(Application::StreamingService* currentService READ getCurrent WRITE setCurrent NOTIFY currentChanged)
public:
    StreamingServices(IStreamingServiceLoader& loader);

    void load();
    Application::StreamingService& get(const QString& name) const;
    const QList<std::shared_ptr<Application::StreamingService>>& getAll() const { return services; }
    
    void setCurrent(Application::StreamingService* service);
    Application::StreamingService* getCurrent() const;

signals:
    void added(StreamingService* service);
    void currentChanged(StreamingService* service);

private:
    ILogger& logger;
    IStreamingServiceLoader& loader;
    QList<std::shared_ptr<MellowPlayer::Application::StreamingService>> services;
    Application::StreamingService* current;
};

END_MELLOWPLAYER_NAMESPACE
