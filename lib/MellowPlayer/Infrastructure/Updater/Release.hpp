#pragma once

#include "Asset.hpp"
#include <QtCore/QDate>
#include <QtCore/QObject>

namespace MellowPlayer::Infrastructure
{
    using AssetList = QList<Asset>;

    class Release : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QString date READ date CONSTANT)
    public:
        Release(const QString& name, const QDate& date, QObject* parent = nullptr);
        Release(const QString& url, const QString& name, const QDate& date, const AssetList& assets, bool preRelease = false,
                QObject* parent = nullptr);

        QString url() const;
        QString name() const;
        QString date() const;

        bool isPreRelease() const;
        const AssetList& assets() const;

        bool operator==(const Release& other) const;
        bool operator!=(const Release& other) const;
        bool operator>(const Release& other) const;
        bool operator>=(const Release& other) const;
        bool operator<(const Release& other) const;
        bool operator<=(const Release& other) const;

        bool isValid() const;

        static const Release& current();

    private:
        QString url_;
        QString name_;
        QDate date_;
        bool preRelease_;
        AssetList assets_;

        static Release current_;
    };
}
