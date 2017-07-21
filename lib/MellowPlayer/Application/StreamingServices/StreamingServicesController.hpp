#pragma once

#include <QList>
#include <QObject>
#include <memory>

namespace MellowPlayer::Application
{
    class StreamingService;
    class ILogger;
    class IStreamingServiceLoader;
    class IStreamingServiceWatcher;

    class StreamingServicesController : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(Application::StreamingService *currentService READ getCurrent WRITE setCurrent NOTIFY currentChanged)
    public:
        StreamingServicesController(IStreamingServiceLoader &loader, IStreamingServiceWatcher &watcher);

        void load();
        Application::StreamingService &get(const QString &name) const;
        const QList<std::shared_ptr<Application::StreamingService>> &getAll() const
        {
            return services;
        }

        void setCurrent(Application::StreamingService *service);
        Application::StreamingService *getCurrent() const;

    signals:
        void added(StreamingService *service);
        void currentChanged(StreamingService *service);

    private:
        ILogger &logger;
        IStreamingServiceLoader &loader;
        IStreamingServiceWatcher &watcher;
        QList<std::shared_ptr<MellowPlayer::Application::StreamingService>> services;
        Application::StreamingService *current;
    };
}
