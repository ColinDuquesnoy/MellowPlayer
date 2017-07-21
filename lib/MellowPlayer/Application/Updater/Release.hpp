#pragma once

#include "Asset.hpp"
#include <QtCore/QDate>
#include <QtCore/QObject>
#include <QtCore/QVersionNumber>

namespace MellowPlayer::Application
{
    using AssetList = QList<Asset>;

    class Release : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ getName CONSTANT)
        Q_PROPERTY(QString date READ getDate CONSTANT)
    public:
        Release(const QString &name, const QDate &date, QObject *parent = nullptr);
        Release(const QString &url, const QString &name, const QDate &date, const AssetList &assets, bool preRelease = false,
                QObject *parent = nullptr);

        QString getUrl() const;
        QString getName() const;
        QString getDate() const;

        bool isPreRelease() const;
        const AssetList &getAssets() const;

        bool operator==(const Release &other) const;
        bool operator!=(const Release &other) const;
        bool operator>(const Release &other) const;
        bool operator>=(const Release &other) const;
        bool operator<(const Release &other) const;
        bool operator<=(const Release &other) const;

        bool isValid() const;

        static const Release &current();

    private:
        QString url_;
        QString name_;
        QDate date_;
        bool preRelease_;
        AssetList assets_;

        static const int REQUIRED_ASSET_COUNT = 3;

        static Release current_;
    };
}
