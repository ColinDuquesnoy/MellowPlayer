#pragma once

#include <MellowPlayer/Domain/Properties.hpp>
#include <QVariantMap>
#include <QtNetwork/QNetworkProxy>

namespace MellowPlayer::Infrastructure
{
    /**
     * QObject wrapper of QNetworkProxy.
     *
     * The wrapper exposes QNetworkProxy properties for use in QML and provides serialization methods from/to a
     * QVariantMap for easy usage with QSettings.
     */
    class NetworkProxy: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
        Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
        Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    public:
        /**
         * Builds a network proxy instance from settings stored in the QVariantMap.
         *
         * Required Keys:
         *  - enabled: bool
         *  - hostName: QString
         *  - port: int
         */
        NetworkProxy(const QVariantMap& qVariantMap=QVariantMap());

        /**
         * Checks if the network proxy is enabled.
         */
        bool isEnabled() const;

        /**
         * Enables or disables network proxy.
         *
         * A disabled network proxy means that the initial application proxy should be used.
         *
         * @param value
         */
        void setEnabled(bool value);

        /**
         * Gets the network proxy host name.
         */
        QString hostName() const;

        /**
         * Sets the network proxy host name.
         */
        void setHostName(const QString& hostName);

        /**
         * Gets the network proxy port
         */
        int port() const;

        /**
         * Sets the network proxy port.
         */
        void setPort(int port);

        /**
         * Tells whether a network proxy is valid. A proxy is valid if it is enabled enabled and
         * if both hostname and port are valid values.
         *
         * @return True if the proxy is valid.
         */
        bool isValid() const;

        /**
         * Create the corresponding QNetworkProxy.
         *
         * @return QNetworkProxy.
         */
        QNetworkProxy create() const;

        /**
         * Returns the network proxy settings as a QVariantMap, ready for use in QSettings.
         */
        QVariantMap toQVariantMap() const;

        /**
         * Returns the network proxy settings as a string with the following format: "$hostName:$port"
         * @return String representation of the network proxy.
         */
        QString toString() const;

    signals:
        /**
         * This signal is emitted when any property of the network proxy has changed.
         */
        void changed();

        /**
         * This signal is emitted when the enabled state of the proxy changed.
         */
        void enabledChanged();

        /**
         * This signal is emitted when the host name property of the proxy changed.
         */
        void hostNameChanged();

        /**
         * This signal is emitted when the port property of the proxy changed.
         */
        void portChanged();

    private:
        bool isEnabled_ = false;
        QString hostName_;
        int port_ = 0;
    };
}
