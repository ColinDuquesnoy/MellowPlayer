#pragma once

#include <QObject>
#include <QString>
#include <QMap>
#include <memory>

namespace MellowPlayer::Domain
{
    class StreamingService;
    class StreamingServices;
    class ISettingsStore;
}

namespace MellowPlayer::Infrastructure
{
    class NetworkProxy;

    /**
     * Manages the list of network proxies of each streaming services.
     */
    class INetworkProxies
    {
    public:
        virtual ~INetworkProxies() = default;

        /**
         * Gets the network proxy of the specified service.
         *
         * @param name Name of the streaming service
         *
         * @return The corresponding network proxy.
         */
        virtual std::shared_ptr<NetworkProxy> get(const QString& name) const = 0;
    };

    /**
     * Implements INetworkProxies and manages persistency of network proxy settings.
     */
    class NetworkProxies: public QObject, public INetworkProxies
    {
    public:
        NetworkProxies(Domain::ISettingsStore& settingsStore,
                       Domain::StreamingServices& streamingServices);

        /**
         * Gets the network proxy of the specified service.
         *
         * @param name Name of the streaming service
         *
         * @return The corresponding network proxy.
         */
        std::shared_ptr<NetworkProxy> get(const QString& name) const override;

    private slots:
        void onStreamingServiceAdded(Domain::StreamingService* service);

    private:
        void add(const QString& serviceName, const std::shared_ptr<NetworkProxy>& networkProxy);
        QString settingUrl(const QString& name) const;

        QMap<QString, std::shared_ptr<NetworkProxy>> items_;
        Domain::ISettingsStore& settingsStore_;
        Domain::StreamingServices& streamingServices_;
    };
}
