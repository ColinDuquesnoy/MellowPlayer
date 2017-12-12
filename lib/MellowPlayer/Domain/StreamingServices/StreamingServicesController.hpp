#pragma once

#include <QList>
#include <QObject>
#include <memory>

namespace MellowPlayer::Domain
{
    class ILogger;
    class IStreamingServiceLoader;
    class IStreamingServiceWatcher;
    class StreamingService;

    class StreamingServices : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(Domain::StreamingService* currentService READ current WRITE setCurrent NOTIFY currentChanged)
    public:
        StreamingServices(IStreamingServiceLoader& loader, IStreamingServiceWatcher& watcher);

        void load();
        Domain::StreamingService& get(const QString& name) const;
        const QList<std::shared_ptr<Domain::StreamingService>>& toList() const
        {
            return services_;
        }

        void setCurrent(Domain::StreamingService* service);
        Domain::StreamingService* current() const;

    signals:
        void added(StreamingService* service);
        void currentChanged(StreamingService* service);

    private:
        ILogger& logger_;
        IStreamingServiceLoader& loader_;
        IStreamingServiceWatcher& watcher_;
        QList<std::shared_ptr<MellowPlayer::Domain::StreamingService>> services_;
        Domain::StreamingService* current_;
    };
}
