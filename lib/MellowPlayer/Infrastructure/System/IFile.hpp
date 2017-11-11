#pragma once

#include <QObject>
#include <QtCore/QString>
#include <MellowPlayer/Domain/Macros.hpp>

namespace MellowPlayer::Infrastructure
{
    class IFile: public QObject
    {
        Q_OBJECT
        WRITABLE_PROPERTY(QString, content, update)
        CONSTANT_PROPERTY(QString, path)
    public:
        virtual ~IFile() = default;

        virtual bool open() = 0;
        virtual bool exists() const = 0;
    };
}
