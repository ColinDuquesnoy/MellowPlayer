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
    class IQtApplication;

    class INetworkProxies
    {
    public:
        virtual ~INetworkProxies() = default;

        virtual std::shared_ptr<NetworkProxy> get(const QString& name) const = 0;
    };

    class NetworkProxies: public QObject, public INetworkProxies
    {
    public:
        NetworkProxies(IQtApplication& qtApplication,
                       Domain::ISettingsStore& settingsStore,
                       Domain::StreamingServices& streamingServices);

        std::shared_ptr<NetworkProxy> get(const QString& name) const override;

    private slots:
        void onStreamingServiceAdded(Domain::StreamingService* service);

    private:
        void add(const QString& serviceName, const std::shared_ptr<NetworkProxy>& networkProxy);
        QString settingUrl(const QString& name) const;

        QMap<QString, std::shared_ptr<NetworkProxy>> items_;
        IQtApplication& qtApplication_;
        Domain::ISettingsStore& settingsStore_;
        Domain::StreamingServices& streamingServices_;
    };
}
