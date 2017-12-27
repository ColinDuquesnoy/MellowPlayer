#pragma once

#include <memory>
#include <QtNetwork/QNetworkProxy>

namespace MellowPlayer::Domain
{
    class StreamingService;
    class StreamingServices;
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class NetworkProxy;
    class INetworkProxies;

    /**
     * Manages the current streaming service network proxy.
     *
     * If the current streaming service's proxy is disabled, the default application proxy is used instead.
     */
    class ApplicationNetworkProxy: public QObject
    {
    public:
        /**
         * @param streamingServices The list of streaming services.
         * @param networkProxies The list of streaming services' network proxies.
         */
        ApplicationNetworkProxy(Domain::StreamingServices& streamingServices, INetworkProxies& networkProxies);

        ~ApplicationNetworkProxy();

    private slots:
        void onCurrentStreamingServiceChanged(Domain::StreamingService* service);

    private:
        void updateNetworkProxy();

    private:
        Domain::ILogger& logger_;
        QNetworkProxy initialNetworkProxy_;
        QString currentServiceName_;
        std::shared_ptr<NetworkProxy> currentNetworkProxy_;
        Domain::StreamingServices& streamingServices_;
        INetworkProxies& networkProxies_;
    };
}
