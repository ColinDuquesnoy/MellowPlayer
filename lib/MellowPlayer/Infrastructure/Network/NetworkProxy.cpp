#include "NetworkProxy.hpp"

using namespace MellowPlayer::Infrastructure;

NetworkProxy::NetworkProxy(const QNetworkProxy& qNetworkProxy)
        : isEnabled_(true),
          hostName_(qNetworkProxy.hostName()),
          port_(qNetworkProxy.port())
{

}

NetworkProxy::NetworkProxy(const QVariantMap& rawData) :
        isEnabled_(rawData["enabled"].toBool()),
        hostName_(rawData["hostName"].toString()),
        port_(rawData["port"].toInt())
{

}

bool NetworkProxy::isEnabled() const
{
    return isEnabled_;
}

void NetworkProxy::setEnabled(bool value)
{
    if (isEnabled_ != value) {
        isEnabled_ = value;
        emit enabledChanged();
        emit changed();
    }
}

QString NetworkProxy::hostName() const
{
    return hostName_;
}

void NetworkProxy::setHostName(const QString& value)
{
    if (hostName() != value) {
        hostName_ = value;
        emit hostNameChanged();
        emit changed();
    }
}

int NetworkProxy::port() const
{
    return port_;
}

void NetworkProxy::setPort(int value)
{
    if (port() != value) {
        port_ = value;
        emit portChanged();
        emit changed();
    }
}

QVariantMap NetworkProxy::rawData() const
{
    QVariantMap rawData;

    rawData["enabled"] = isEnabled_;
    rawData["port"] = port_;
    rawData["hostName"] = hostName_;

    return rawData;
}

QNetworkProxy NetworkProxy::create() const
{
    if (isValid())
        return QNetworkProxy(QNetworkProxy::HttpProxy, hostName_, static_cast<quint16 >(port_));
    return QNetworkProxy();
}

bool NetworkProxy::isValid() const
{
    return isEnabled_ && !hostName_.isEmpty() && port_ != 0;
}
