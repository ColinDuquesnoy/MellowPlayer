#pragma once

#include "IIniFile.hpp"
#include <QtCore/QVariant>
#include <QtCore/QSettings>

namespace MellowPlayer::Infrastructure
{
    class IniFile: public IIniFile
    {
    public:
        IniFile(const QString& path);

        QString path() const override;
        virtual QVariant value(const QString& key) const override;
        virtual QVariant value(const QString& key, const QVariant& defaultValue) const override;
    private:
        QSettings iniFile_;
        QString path_;

    };
}

