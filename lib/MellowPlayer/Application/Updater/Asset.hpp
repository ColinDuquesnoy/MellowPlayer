#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Application
{
    class Asset
    {
    public:
        Asset();
        Asset(const QString &name, const QString &url);

        QString getName() const;
        QString getUrl() const;

        bool isAppImage() const;
        bool isWindowsInstaller() const;
        bool isDmg() const;

        bool isValid() const;

    private:
        QString name_;
        QString url_;
    };
}
