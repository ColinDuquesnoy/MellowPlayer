#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>

using namespace MellowPlayer::Infrastructure;

NetworkProxy::NetworkProxy(const QVariantMap& qVariantMap) :
        isEnabled_(qVariantMap["enabled"].toBool()),
        hostName_(qVariantMap["hostName"].toString()),
        port_(qVariantMap["port"].toInt())
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

QVariantMap NetworkProxy::toQVariantMap() const
{
    QVariantMap qVariantMap;

    qVariantMap["enabled"] = isEnabled_;
    qVariantMap["port"] = port_;
    qVariantMap["hostName"] = hostName_;

    return qVariantMap;
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

QString NetworkProxy::toString() const
{
    return QString("%1:%2").arg(hostName_).arg(port_);
}
