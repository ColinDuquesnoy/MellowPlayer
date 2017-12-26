#include "NetworkProxy.hpp"

using namespace MellowPlayer::Infrastructure;

NetworkProxy::NetworkProxy(const QVariantMap& rawData): rawData_(rawData)
{
}

bool NetworkProxy::isEnabled() const {
    return rawData_["enabled"].toBool();
}

void NetworkProxy::setEnabled(bool value) {
    if (isEnabled() != value) {
        rawData_["enabled"] = value;
        emit enabledChanged();
        emit changed();
    }
}

QString NetworkProxy::hostName() const
{
    return rawData_["hostName"].toString();
}

void NetworkProxy::setHostName(const QString& value)
{
    if(hostName() != value){
        rawData_["hostName"] = value;
        emit hostNameChanged();
        emit changed();
    }
}

int NetworkProxy::port() const
{
    return rawData_["port"].toInt();
}

void NetworkProxy::setPort(int value)
{
    if (port() != value) {
        rawData_["port"] = value;
        emit portChanged();
        emit changed();
    }
}

QVariantMap NetworkProxy::rawData() const
{
    return rawData_;
}

QNetworkProxy NetworkProxy::create() const {
    return QNetworkProxy(isEnabled() ? QNetworkProxy::HttpProxy : QNetworkProxy::DefaultProxy,
                         hostName(), static_cast<quint16 >(port()));
}
