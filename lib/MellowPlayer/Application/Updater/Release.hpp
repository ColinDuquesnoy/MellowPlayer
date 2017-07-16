#pragma once

#include <QtCore/QObject>
#include <QtCore/QVersionNumber>
#include <QtCore/QDate>
#include "Asset.hpp"

namespace MellowPlayer::Application {

    using AssetList = QList<Asset>;

    class Release: public QObject {
        Q_OBJECT
        Q_PROPERTY(QString name READ getName CONSTANT)
        Q_PROPERTY(QString date READ getDate CONSTANT)
        Q_PROPERTY(QString description READ getDescription CONSTANT)
    public:
        Release(const QString& name, const QDate& date, QObject* parent= nullptr);
        Release(const QString& url, const QString& version, const QDate& date, const QString& description,
                const AssetList& assets, bool preRelease=false, QObject* parent=nullptr);

        QString getName() const;
        QString getDate() const;
        const QString& getDescription() const;
        bool isPreRelease() const;
        const AssetList& getAssets() const;

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
        QString description_;
        bool preRelease_;
        AssetList assets_;

        static const int REQUIRED_ASSET_COUNT = 3;

        static Release current_;
    };
}
