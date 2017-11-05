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
        virtual QVariant value(const QString& key, const QVariant& defaultValue) const;

    private:
        QSettings iniFile_;

    };
}

