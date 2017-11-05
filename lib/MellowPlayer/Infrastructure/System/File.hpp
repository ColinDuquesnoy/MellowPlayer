#pragma once

#include "IFile.hpp"
#include <QtCore/QString>
#include <QtCore/QFile>

namespace MellowPlayer::Infrastructure
{
    class File: public IFile
    {
    public:
        File(const QString& path);

        QString path() const override;
        bool openReadOnly() override;
        bool exists() const override;
        QString readAll() override;

    private:
        QString path_;
        QFile file_;
    };
}
