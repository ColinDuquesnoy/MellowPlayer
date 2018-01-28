#pragma once

#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class StreamingServiceScript : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString code READ code NOTIFY codeChanged);
        Q_PROPERTY(QString path READ path CONSTANT);

    public:
        StreamingServiceScript(const QString& code, const QString& path);

        bool isValid() const;

        QString constants() const;

        QString code() const;
        void setCode(const QString& value);

        const QString& path() const;
    signals:
        void codeChanged(QString);

    private:
        QString code_;
        QString path_;
    };
}
