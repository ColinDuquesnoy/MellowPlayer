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

        bool open() override;
        bool exists() const override;

    private:
        QString path_;
        QFile file_;
    };
}
