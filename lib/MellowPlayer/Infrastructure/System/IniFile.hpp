#pragma once

#include "IIniFile.hpp"
#include <QtCore/QVariant>
#include <QtCore/QSettings>

namespace MellowPlayer::Infrastructure
{
    class IFile;

    class IniFile: public IIniFile
    {
    public:
        IniFile(const std::shared_ptr<IFile>& file);

        QString path() const override;
        virtual QVariant value(const QString& key) const override;
    private:
        std::shared_ptr<IFile> file_;
        QSettings settings_;
    };
}

