#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Infrastructure
{
    class IFile
    {
    public:
        virtual ~IFile() = default;

        virtual QString path() const = 0;
        virtual bool openReadOnly() = 0;
        virtual bool exists() const = 0;
        virtual QString readAll() = 0;
    };
}
